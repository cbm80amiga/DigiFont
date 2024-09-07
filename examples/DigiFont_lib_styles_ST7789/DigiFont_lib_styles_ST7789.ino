// DigiFont library example
// Styles demo on ST7789 LCD
// (c) 2020-24 Pawel A. Hernik
// YouTube video: https://youtu.be/X6PjfhcNE98

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
#define SCR_HT 240
//#define SCR_HT 320

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

void setup(void) 
{
  Serial.begin(9600);
  lcd.init(SCR_WD,SCR_HT);
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  digi.setSpacing(4);
}

unsigned long ms,demoTime=5000;
char buf[20];

void style1()
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Style 1 or 7");
  ms=millis();
  int x,y=30;
  while(millis()-ms<demoTime) {
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,40,0));
    digi.setSize1(64,140,13);
    x=digi.printNumber1(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(40,0,40));
    digi.setSize1(44,78,9);
    digi.printNumber1("6:45",x+10,y);
    digi.setColors(RED,RGBto565(40,0,0));
    digi.setSize1(30,50,5);
    digi.printNumber1(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void style2()
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Style 2 or 7");
  ms=millis();
  int x,y=30;
  while(millis()-ms<demoTime) {
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,40,0));
    digi.setSize2(64,140,13);
    x=digi.printNumber2(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(40,0,40));
    digi.setSize2(44,78,9);
    digi.printNumber2("6:45",x+10,y);
    digi.setColors(RED,RGBto565(40,0,0));
    digi.setSize2(30,50,5);
    digi.printNumber2(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void style2c()
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Style 2c or 7");
  ms=millis();
  int x,y=30;
  while(millis()-ms<demoTime) {
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,180,0), RGBto565(0,40,0));
    digi.setSize2(64,140,13);
    x=digi.printNumber2c(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(180,0,180),RGBto565(40,0,40));
    digi.setSize2(44,78,9);
    digi.printNumber2c("6:45",x+10,y);
    digi.setColors(RED,RGBto565(180,0,0),RGBto565(40,0,0));
    digi.setSize2(30,50,5);
    digi.printNumber2c(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void style3()
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Style 3");
  ms=millis();
  int x,y=30;
  while(millis()-ms<demoTime) {
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,40,0));
    digi.setSize3(64,140,13);
    x=digi.printNumber3(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(40,0,40));
    digi.setSize3(44,78,9);
    digi.printNumber3("6:45",x+10,y);
    digi.setColors(RED,RGBto565(40,0,0));
    digi.setSize3(30,50,5);
    digi.printNumber3(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void styleF()
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Style F");
  ms=millis();
  int x,y=30;
  while(millis()-ms<demoTime) {
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,40,0));
    digi.setSizeF(64,140,13);
    x=digi.printNumberF(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(40,0,40));
    digi.setSizeF(44,78,9);
    digi.printNumberF("6:45",x+10,y);
    digi.setColors(RED,RGBto565(40,0,0));
    digi.setSizeF(30,50,5);
    digi.printNumberF(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void styleO()
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Style O");
  ms=millis();
  int x,y=30;
  while(millis()-ms<demoTime) {
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,0,0));
    digi.setSizeO(64,140,13);
    x=digi.printNumberO(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(0,0,0));
    digi.setSizeO(44,78,9);
    digi.printNumberO("6:45",x+10,y);
    digi.setColors(RED,RGBto565(0,0,0));
    digi.setSizeO(30,50,5);
    digi.printNumberO(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void loop() 
{
  style1(); // or 7
  style2(); // or 7
  style2c(); // or 7
  style3();
  styleF();
  styleO();
}

