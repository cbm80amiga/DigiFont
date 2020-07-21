// DigiFont library example
// Digital clock example on HX1230 LCD
// (c) 2020 Pawel A. Hernik

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

void demoClock1(int t)
{
  int w=22;
  font.setSize1(w-1,40,t);
  int y=(SCR_HT-40)/2;
  ms=millis();
  while(millis()-ms<5000) {
    lcd.cls();
    font.drawDigit1(random(0,3),0*w,y);
    font.drawDigit1(random(0,4),1*w,y);
    font.drawDigit1(':',1+2*w,y);
    font.drawDigit1(random(0,6),t+3+2*w,y);
    font.drawDigit1(random(0,10),t+3+3*w,y);
    lcd.display();
    delay(600);
  }
}

void demoClock2(int t)
{
  int w=21;
  font.setSize2(w-1,40,t);
  int y=(SCR_HT-40)/2;
  ms=millis();
  while(millis()-ms<5000) {
    lcd.cls();
    font.drawDigit2(random(0,3),0*w,y);
    font.drawDigit2(random(0,4),1*w,y);
    font.drawDigit2(':',1+2*w,y);
    font.drawDigit2(random(0,6),t+3+2*w,y);
    font.drawDigit2(random(0,10),t+3+3*w,y);
    lcd.display();
    delay(600);
  }
}

void loop() 
{
  demoClock1(5);
  demoClock2(7);
  demoClock2(5);
}


