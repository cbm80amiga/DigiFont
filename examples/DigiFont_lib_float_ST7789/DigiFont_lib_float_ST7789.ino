// DigiFont library example
// Floating point values on ST7789 IPS display
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
  font.setColors(RED,RGBto565(40,0,0));
  lcd.fillRect(0,2*SCR_HT/3,SCR_WD,SCR_HT/3,RGBto565(150,150,150));
}

char buf[20];
long v=-99999;
int w=SCR_WD/7;

void demoFloat()
{
  font.setSpacing(6);
  dtostrf((float)v/100.0,7,2,buf);

  font.setColors(RED,RGBto565(70,0,0));
  font.setSize1(w-4,w*2,7);
  font.printNumber1(buf,6,0);

  font.setColors(GREEN,RGBto565(0,50,0));
  font.setSize2(w-4,w*2,7);
  font.printNumber2(buf,6,w*2+15);

  font.setColors(RGBto565(30,30,30),RGBto565(130,130,130));
  font.setSize2(w-4,w*2,7);
  font.printNumber2(buf,6,w*4+30);

  v+=4901;
  if(v>999999) v=-99999;
}

void loop() 
{
  demoFloat();
}

