// DigiFont library example
// Ultimate 7-segment demo on ST7789
// (c) 2020-24 Pawel A. Hernik
// YouTube videos:
// https://youtu.be/X6PjfhcNE98
// https://youtu.be/Z_YCfJZn_bA

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
  digi.setColors(RED,RGBto565(40,0,0));
}

unsigned long ms;
char buf[20];

void style7(int st)
{
  long cnt = 23456;
  lcd.fillScreen(BLACK);
  digi.setColors(RED,RGBto565(40,0,0));
  digi.setSpacing(2);
  ms=millis();
  int x,y=30;
  while(millis()-ms<5000) {
    snprintf(buf,19,"Style #7 s=%d",st);
    lcd.setCursor(0,0);
    lcd.print(buf);
    snprintf(buf,6,"%05ld",cnt);
    digi.setColors(GREEN,RGBto565(0,40,0));
    digi.setSize7(64,140,13,st);
    x=digi.printNumber7(buf+4,0,y);
    digi.setColors(RGBto565(250,0,250),RGBto565(40,0,40));
    digi.setSize7(44,78,9,st);
    digi.printNumber7("6:45",x+10,y);
    digi.setColors(RED,RGBto565(40,0,0));
    digi.setSize7(30,50,5,st>2?2:st);
    digi.printNumber7(buf,x+10,120);
    delay(300);
    cnt+=111;
  }
}

void misc_3()
{
  long cnt = 0;
  lcd.fillScreen(BLACK);
  digi.setColors(GREEN,RGBto565(0,40,0));
  digi.setSpacing(4);
  ms=millis();
  int w=SCR_WD/3,h=140;
  while(millis()-ms<5000) {
    for(int i=0;i<3;i++) { digi.setSize7(w-4,h,11,i+1); digi.drawDigit7(cnt,w*i,0); }
    if(++cnt>9) cnt=0;
    delay(400);
  }
}

void misc_4_5()
{
  long cnt = 0;
  lcd.fillScreen(BLACK);
  digi.setColors(GREEN,RGBto565(0,40,0));
  digi.setSpacing(4);
  ms=millis();
  int w=SCR_WD/4,h=80;
  int w2=SCR_WD/5,h2=65;
  while(millis()-ms<5000) {
    //h=50; cnt=8;
    for(int i=0;i<4;i++) { digi.setSize7(w-4,h,9,i); digi.drawDigit7(cnt,w*i,0); }
    for(int i=0;i<5;i++) { digi.setSize7(w2-4,h2,7,i>2?2:i); digi.drawDigit7(cnt,w2*i,90); }
    if(++cnt>9) cnt=0;
    delay(400);
  }
}

void demo()
{
  lcd.fillScreen(BLACK);
  digi.setColors(GREEN,RGBto565(0,40,0));
  digi.setSpacing(4);
  int w=SCR_WD/4,h=100;
  lcd.setCursor((240-10*12)/2,0);
  lcd.print("segThick=7");
  for(int i=0;i<4;i++) {
    digi.setSize7(w-4,h,9,i);
    digi.drawDigit7(8,w*i,40);
    snprintf(buf,19,"s=%d",i);
    lcd.setCursor(w*i+10,20);
    lcd.print(buf);
  }
  delay(9000);
}

void loop() 
{
  demo();
  for(int i=0;i<=4;i++) style7(i);
  misc_3();
  misc_4_5();
}

