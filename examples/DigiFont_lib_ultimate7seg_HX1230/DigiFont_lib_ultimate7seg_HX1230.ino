// DigiFont library example
// Ultimate 7-segment demo on HX1230 LCD
// (c) 2020 Pawel A. Hernik
// YouTube videos:
// https://youtu.be/X6PjfhcNE98

/*
  HX1230 96x68 LCD connections (header on bottom, from left):
  #1 RST - D6 or any digital
  #2 CE  - D7 or any digital
  #3 N/C
  #4 DIN - D11/MOSI 
  #5 CLK - D13/SCK
  #6 VCC - 3V3
  #7 BL  - 3V3 or any digital
  #8 GND - GND
*/

#define LCD_RST 6
#define LCD_CS  7
#define LCD_BL  8

#include "HX1230_FB.h"
#include <SPI.h>
HX1230_FB lcd(LCD_RST, LCD_CS);

#include "c64enh_font.h"

// -----------------
#include "DigiFont.h"
// needed for DigiFont library initialization, define your customLineH, customLineV and customRect
void customLineH(int x0,int x1, int y, int c) { lcd.drawLineHfast(x0,x1,y,c); }
void customLineV(int x, int y0,int y1, int c) { lcd.drawLineVfast(x,y0,y1,c); } 
void customRect(int x, int y,int w,int h, int c) { lcd.fillRect(x,y,w,h,c); } 
DigiFont font(customLineH,customLineV,customRect);
// -----------------

void setup(void) 
{
  Serial.begin(9600);
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  lcd.init();
  lcd.cls();
  lcd.display();
  font.setColors(1,0);
}

unsigned long ms;
char buf[20];

void style7(int st)
{
  long cnt = 23456;
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  ms=millis();
  while(millis()-ms<5000) {
    snprintf(buf,19,"Style #7 s=%d",st);
    lcd.printStr(ALIGN_CENTER, 0, buf);
    snprintf(buf,6,"%05ld",cnt);
    font.setSize7(30,68-10,9,st);
    font.printNumber7(buf+4,0,10);
    font.setSize7(17,35,5,st>2?2:st);
    font.printNumber7("6:45",34,10);
    font.setSize7(10,20,3,st>1?1:st);
    font.printNumber7(buf,34,48);
    lcd.display();
    delay(300);
    cnt+=111;
  }
}

void misc_3()
{
  long cnt = 0;
  lcd.cls();
  font.setColors(1,0);
  font.setSpacing(2);
  ms=millis();
  int w=SCR_WD/3,h=60;
  while(millis()-ms<5000) {
    for(int i=0;i<3;i++) { font.setSize7(w-2,h,9,i+1); font.drawDigit7(cnt,w*i,0); }
    if(++cnt>9) cnt=0;
    lcd.display();
    delay(400);
  }
}

void misc_4_5()
{
  long cnt = 0;
  lcd.cls();
  font.setColors(1,0);
  font.setSpacing(2);
  ms=millis();
  int w=SCR_WD/4,h=38;
  int w2=SCR_WD/5,h2=29;
  while(millis()-ms<5000) {
    //h=50; cnt=8;
    for(int i=0;i<4;i++) { font.setSize7(w-2,h,7,i); font.drawDigit7(cnt,w*i,0); }
    for(int i=0;i<5;i++) { font.setSize7(w2-2,h2,5,i>2?2:i); font.drawDigit7(cnt,w2*i,68-h2); }
    if(++cnt>9) cnt=0;
    lcd.display();
    delay(400);
  }
}

void demo()
{
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  int w=SCR_WD/4,h=48;
  lcd.printStr(ALIGN_CENTER, 0, "segThick=7");
  for(int i=0;i<4;i++) {
    font.setSize7(w-2,h,7,i);
    font.drawDigit7(8,w*i,68-h);
    snprintf(buf,19,"s=%d",i);
    lcd.printStr(i*w, 10, buf);
  }
  lcd.display();
  delay(9000);
}

void loop() 
{
  demo();
  style7(0);
  style7(1);
  style7(2);
  style7(3);
  style7(4);
  misc_3();
  misc_4_5();
}

