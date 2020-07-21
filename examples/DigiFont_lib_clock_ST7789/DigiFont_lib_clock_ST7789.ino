// DigiFont library example
// Digital clock example on ST7789 IPS display
// (c) 2020 Pawel A. Hernik

/*
 ST7789 240x240 IPS (without CS pin) connections (only 6 wires required):

 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> PA5/SCK
 #04 SDA -> PA7/MOSI
 #05 RES -> PA0 or any digital
 #06 DC  -> PA1 or any digital
 #07 BLK -> NC
*/

#define SCR_WD 240
#define SCR_HT 240
#include <SPI.h>
#include <Adafruit_GFX.h>
#define TFT_DC    10
#define TFT_RST   9
#include <Arduino_ST7789_Fast.h>
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

// -----------------
#include "DigiFont.h"
// needed for DigiFont library initialization, define your customLineH, customLineV and customRect
void customLineH(int x0,int x1, int y, int c) { lcd.drawFastHLine(x0,y,x1-x0+1,c); }
void customLineV(int x, int y0,int y1, int c) { lcd.drawFastVLine(x,y0,y1-y0+1,c); } 
void customRect(int x, int y,int w,int h, int c) { lcd.fillRect(x,y,w,h,c); } 
DigiFont font(customLineH,customLineV,customRect);
// -----------------

void setup(void) 
{
  Serial.begin(9600);
  lcd.init();
  lcd.fillScreen(BLACK);
}

unsigned long ms;

void demoClock1(int t)
{
  lcd.fillScreen(BLACK);
  font.setColors(RED,RGBto565(60,0,0));
  int w=(SCR_HT-t-10)/4;
  font.setSize1(w-3,w*2,t);
  int y=(SCR_HT-w*2)/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.drawDigit1(random(0,3),0*w,y);
    font.drawDigit1(random(0,4),1*w,y);
    font.drawDigit1(':',2*w+5-3,y);
    font.drawDigit1(random(0,6),t+10-3+2*w,y);
    font.drawDigit1(random(0,10),t+10-3+3*w,y);
    delay(600);
  }
}

void demoClock2(int t)
{
  lcd.fillScreen(BLACK);
  font.setColors(GREEN,RGBto565(0,40,0));
  int w=(SCR_HT-t-10)/4;
  font.setSize2(w-3,w*2,t);
  int y=(SCR_HT-w*2)/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.drawDigit2(random(0,3),0*w,y);
    font.drawDigit2(random(0,4),1*w,y);
    font.drawDigit2(':',2*w+5-3,y);
    font.drawDigit2(random(0,6),t+10-3+2*w,y);
    font.drawDigit2(random(0,10),t+10-3+3*w,y);
    delay(600);
  }
}

void loop() 
{
  demoClock1(10);
  demoClock2(14);
  demoClock2(10);
}


