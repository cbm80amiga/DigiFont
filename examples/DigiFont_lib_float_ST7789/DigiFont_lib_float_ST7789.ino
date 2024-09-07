// DigiFont library example
// Floating point values on ST7789 IPS display
// (c) 2020-24 Pawel A. Hernik

/*
ST7789 240x240 1.3" IPS (without CS pin) - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> D9 /PA0 or any digital (HW RESET is required to properly initialize LCD without CS)
 #06 DC  -> D10/PA1 or any digital
 #07 BLK -> NC

ST7789 240x280 1.69" IPS - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> optional
 #06 DC  -> D10 or any digital
 #07 CS  -> D9 or any digital
 #08 BLK -> VCC

ST7789 170x320 1.9" IPS - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> optional
 #06 DC  -> D10 or any digital
 #07 CS  -> D9 or any digital
 #08 BLK -> VCC

ST7789 240x320 2.0" IPS - only 4+2 wires required:
 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> optional
 #06 DC  -> D10 or any digital
 #07 CS  -> D9 or any digital
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include "ST7789_AVR.h"

#define SCR_WD 240
#define SCR_HT 320
//#define SCR_HT 240

#define TFT_DC   10
#define TFT_CS    9  // with CS
#define TFT_RST  -1  // with CS
ST7789_AVR lcd = ST7789_AVR(TFT_DC, TFT_RST, TFT_CS);

// -----------------
#include "DigiFont.h"
// needed for DigiFont library initialization, define your customLineH, customLineV and customRect
void customLineH(int x0,int x1, int y, int c) { lcd.drawFastHLine(x0,y,x1-x0+1,c); }
void customLineV(int x, int y0,int y1, int c) { lcd.drawFastVLine(x,y0,y1-y0+1,c); } 
void customRect(int x, int y,int w,int h, int c) { lcd.fillRect(x,y,w,h,c); } 
DigiFont digi(customLineH,customLineV,customRect);
// -----------------

char buf[20];
long v=-99999;
int w=SCR_WD/7; // 34 for 240px screen

void setup(void) 
{
  Serial.begin(9600);
  lcd.init(SCR_WD,SCR_HT);
  lcd.fillScreen(BLACK);
  digi.setColors(RED,RGBto565(40,0,0));
  lcd.fillRect(0,w*4+30-6,SCR_WD,w*2+12,RGBto565(150,150,150));
}

// 14,320 bytes in PROGMEM - style 2/2c mixed
void demoFloat()
{
  digi.setSpacing(6);
  dtostrf((float)v/100.0,7,2,buf);

  //digi.setColors(RED,RGBto565(70,0,0));
  //digi.setSize1(w-4,w*2,7);
  //digi.printNumber1(buf,6,0);

  digi.setColors(RGBto565(250,50,50),RGBto565(160,20,20),RGBto565(40,0,0));
  //digi.setColors(GREEN,RGBto565(0,50,0));
  //digi.setSize2(w-4,w*2,7);
  digi.setSize2(w-4,w*2,9);
  digi.printNumber2c(buf,6,0);

  digi.setColors(GREEN,RGBto565(0,50,0));
  digi.setSize2(w-4,w*2,7);
  digi.printNumber2(buf,6,w*2+15);

  digi.setColors(RGBto565(30,30,30),RGBto565(130,130,130));
  digi.setSize2(w-4,w*2,7);
  digi.printNumber2(buf,6,w*4+30);

#if SCR_HT==320
  digi.setColors(RGBto565(0,250,250),RGBto565(0,160,160),RGBto565(0,40,40));
  digi.setSize2(40,68,11);
  digi.printNumber2c("22.3'C",6,w*6+45);
#endif

  v+=4901;
  if(v>999999) v=-99999;
}

// 13,456 bytes in PROGMEM - only style 7
void demoFloat7()
{
  digi.setSpacing(6);
  dtostrf((float)v/100.0,7,2,buf);

  digi.setColors(RGBto565(250,50,50),RGBto565(200,20,20),RGBto565(40,0,0));
  digi.setSize7(w-4,w*2,9,3);
  digi.printNumber7(buf,6,0);

  digi.setColors(GREEN,RGBto565(0,50,0));
  digi.setSize7(w-4,w*2,7,2);
  digi.printNumber7(buf,6,w*2+15);

  digi.setColors(RGBto565(30,30,30),RGBto565(130,130,130));
  digi.setSize7(w-4,w*2,7,2);
  digi.printNumber7(buf,6,w*4+30);

#if SCR_HT==320
  digi.setColors(RGBto565(0,250,250),RGBto565(0,190,190),RGBto565(0,40,40));
  digi.setSize7(40,68,11,4);
  digi.printNumber7("23.4'C",6,w*6+45);
#endif

  v+=4901;
  if(v>999999) v=-99999;
}

void loop() 
{
  demoFloat7();
}

