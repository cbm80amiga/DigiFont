// DigiFont library example
// Special mixed modes / HX1230 LCD
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
void customRectD(int x, int y,int w,int h, int c) { lcd.fillRectD(x,y,w,h,c); } 
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

int cnt=0;
void special()
{
  //lcd.cls();
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

