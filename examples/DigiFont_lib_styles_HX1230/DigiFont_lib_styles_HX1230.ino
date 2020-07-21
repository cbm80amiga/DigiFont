// DigiFont library example
// Styles demo on HX1230 LCD
// (c) 2020 Pawel A. Hernik
// YouTube video: https://youtu.be/X6PjfhcNE98

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

void style1()
{
  long cnt = 23456;
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  lcd.printStr(ALIGN_CENTER, 0, "Style #1");
  ms=millis();
  while(millis()-ms<5000) {
    snprintf(buf,6,"%05ld",cnt);
    font.setSize1(30,68-10,7);
    font.printNumber1(buf+4,0,10);
    font.setSize1(17,35,5);
    font.printNumber1("6:45",34,10);
    font.setSize1(10,20,3);
    font.printNumber1(buf,34,48);
    lcd.display();
    delay(300);
    cnt+=111;
  }
}

void style2()
{
  long cnt = 23456;
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  lcd.printStr(ALIGN_CENTER, 0, "Style #2");
  ms=millis();
  while(millis()-ms<5000) {
    snprintf(buf,6,"%05ld",cnt);
    font.setSize2(30,68-10,7);
    font.printNumber2(buf+4,0,10);
    font.setSize2(17,35,5);
    font.printNumber2("6:45",34,10);
    font.setSize2(10,20,3);
    font.printNumber2(buf,34,48);
    lcd.display();
    delay(300);
    cnt+=111;
  }
}

void style3()
{
  long cnt = 23456;
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  lcd.printStr(ALIGN_CENTER, 0, "Style #3");
  ms=millis();
  while(millis()-ms<5000) {
    snprintf(buf,6,"%05ld",cnt);
    font.setSize3(30,68-10,6);
    font.printNumber3(buf+4,0,10);
    font.setSize3(17,35,3);
    font.printNumber3("6:45",34,10);
    font.setSize3(10,20,2);
    font.printNumber3(buf,34,48);
    lcd.display();
    delay(300);
    cnt+=111;
  }
}

void style4()
{
  long cnt = 23456;
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  lcd.printStr(ALIGN_CENTER, 0, "Style #4");
  ms=millis();
  while(millis()-ms<5000) {
    snprintf(buf,6,"%05ld",cnt);
    font.setSize4(30,68-10,9);
    font.printNumber4(buf+4,0,10);
    font.setSize4(17,35,5);
    font.printNumber4("6:45",34,10);
    font.setSize4(10,20,3);
    font.printNumber4(buf,34,48);
    lcd.display();
    delay(300);
    cnt+=111;
  }
}

void style5()
{
  long cnt = 23456;
  lcd.cls();
  lcd.setFont(c64enh);
  font.setColors(1,0);
  font.setSpacing(2);
  ms=millis();
  while(millis()-ms<5000) {
    lcd.printStr(ALIGN_CENTER, 0, "Style #5");
    snprintf(buf,6,"%05ld",cnt);
    font.setSize5(30,68-10,10);
    font.printNumber5(buf+4,0,10);
    font.setSize5(17,35,5);
    font.printNumber5("6:45",34,10);
    font.setSize5(10,20,4);
    font.printNumber5(buf,34,48);
    lcd.display();
    delay(300);
    cnt+=111;
  }
}

void loop() 
{
  style1();
  style2();
  style3();
  style4();
  style5();
}

