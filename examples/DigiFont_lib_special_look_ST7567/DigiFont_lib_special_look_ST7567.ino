// DigiFont library example
// Special mixed mode / ST7567 LCD
// (c) 2020 Pawel A. Hernik
// YouTube videos:
// https://youtu.be/X6PjfhcNE98
// https://youtu.be/OPq9aBJP-pc

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
void customRectD(int x, int y,int w,int h, int c) { lcd.fillRectD(x,y,w,h,c); } 
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

int cnt=0;
void special()
{
  lcd.cls();
  //lcd.fillRectD(0,0,96,68,1);
  int w=SCR_WD/4,h=50;
  font.setClearBg(1);
  font.setSize5(w-2,h,8);
  font.drawDigit5(cnt,0,0);
  font.setClearBg(0);
  font.setSize4(w-2-4,h-4,4);
  font.drawDigit4(cnt,2,2);

  font.setClearBg(1);
  font.setSize5(w-2,h,8);
  font.drawDigit5(cnt,w*1,0);
  font.setClearBg(0);
  font.setSize4(w-2-2,h-2,8-2);
  lcd.setDither(4);
  font.init(customLineH,customLineV,customRectD);
  font.drawDigit4(cnt,w*1+1,1);
  font.init(customLineH,customLineV,customRect);

  font.setClearBg(1);
  font.setSize5(w-2,h,9);
  font.drawDigit5(cnt,w*2,0);
  font.setClearBg(0);
  font.setSize4(w-2-2,h-2,9-2);
  lcd.setDither(8);
  font.init(customLineH,customLineV,customRectD);
  font.drawDigit4(cnt,w*2+1,1);
  font.init(customLineH,customLineV,customRect);

  font.setClearBg(1);
  font.setSize5(w-2,h,9);
  font.drawDigit5(cnt,w*3,0);
  font.setClearBg(0);
  font.setSize4(w-2-2,h-2,9-2);
  lcd.setDither(12);
  font.init(customLineH,customLineV,customRectD);
  font.drawDigit4(cnt,w*3+1,1);
  font.init(customLineH,customLineV,customRect);

  if(++cnt>9) cnt=0;
  lcd.display();
  delay(500);
}


void loop() 
{
  special();
}

