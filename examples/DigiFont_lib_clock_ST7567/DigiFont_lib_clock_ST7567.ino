// DigiFont library example
// Digital clock example on ST7567 LCD
// (c) 2020 Pawel A. Hernik

/*
 128x64 ST7567 connections in SPI mode (only 5-6 wires between LCD and MCU):

 #01 LED  -> D6, GND or any pin via resistor
 #02 RST  -> D9 or any pin
 #03 CS   -> D10 or any pin
 #04 DC   -> D8 or any pin
 #05 SCK  -> D13/SCK
 #06 SDI  -> D11/MOSI
 #07 3V3  -> VCC (3.3V)
 #08 GND  -> GND
*/

#define LCD_BL  6
#define LCD_CS  10
#define LCD_DC  8
#define LCD_RST 9

#include "ST7567_FB.h"
#include <SPI.h>
ST7567_FB lcd(LCD_DC, LCD_RST, LCD_CS);

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
  digitalWrite(LCD_BL, LOW);
  lcd.init();
  lcd.cls();
  lcd.display();
  font.setColors(1,0);
}

unsigned long ms;

void demoClock1(int t)
{
  int w=29;
  font.setSize1(w-1,60,t);
  int y=(SCR_HT-60)/2;
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
  int w=29;
  font.setSize2(w-1,60,t);
  int y=(SCR_HT-60)/2;
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


