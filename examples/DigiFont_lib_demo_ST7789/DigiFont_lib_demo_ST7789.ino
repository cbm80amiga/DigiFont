// DigiFont library example
// Demo on ST7789 IPS display
// (c) 2020 Pawel A. Hernik
// YouTube video: https://youtu.be/X6PjfhcNE98

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
}

unsigned long ms;
char buf[20];

void demoClock1(int t)
{
  font.setColors(RED,RGBto565(40,0,0));
  int s1=4,s2=8;
  lcd.fillScreen(BLACK);
  int w=(SCR_HT-t-s2*2)/4;
  font.setSize1(w-s1,w*2,t);
  int y=(SCR_HT-w*2)/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.drawDigit1(random(0,3),0*w,y);
    font.drawDigit1(random(0,4),1*w,y);
    font.drawDigit1(':',2*w+s2-s1,y);
    font.drawDigit1(random(0,6),t+2*s2-s1+2*w,y);
    font.drawDigit1(random(0,10),t+2*s2-s1+3*w,y);
    delay(500);
  }
}

void demoClock2(int t)
{
  font.setColors(GREEN,RGBto565(0,40,0));
  int s1=4,s2=8;
  lcd.fillScreen(BLACK);
  int w=(SCR_HT-t-s2*2)/4;
  font.setSize2(w-s1,w*2,t);
  int y=(SCR_HT-w*2)/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.drawDigit2(random(0,3),0*w,y);
    font.drawDigit2(random(0,4),1*w,y);
    font.drawDigit2(':',2*w+s2-s1,y);
    font.drawDigit2(random(0,6),t+2*s2-s1+2*w,y);
    font.drawDigit2(random(0,10),t+2*s2-s1+3*w,y);
    delay(500);
  }
}

void demoClock2c(int t)
{
  font.setColors(RGBto565(0,250,0),RGBto565(0,180,0),RGBto565(0,40,0));
  int s1=4,s2=8;
  lcd.fillScreen(BLACK);
  int w=(SCR_HT-t-s2*2)/4;
  font.setSize2(w-s1,w*2,t);
  int y=(SCR_HT-w*2)/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.drawDigit2c(random(0,3),0*w,y);
    font.drawDigit2c(random(0,4),1*w,y);
    font.drawDigit2c(':',2*w+s2-s1,y);
    font.drawDigit2c(random(0,6),t+2*s2-s1+2*w,y);
    font.drawDigit2c(random(0,10),t+2*s2-s1+3*w,y);
    delay(500);
  }
}

void demoBig()
{
  lcd.fillScreen(BLACK);
  int i=0;
  int w=SCR_WD/3;
  ms=millis();
  while(millis()-ms<6000) {
    font.setColors(RED,RGBto565(50,0,0));
    font.setSize1(w-8,SCR_HT,10);
    font.drawDigit1(i%10,0*w,0);
    font.setSize2(w-8,SCR_HT,12);
    font.setColors(GREEN,RGBto565(0,40,0));
    font.drawDigit2(i%10,1*w,0);
    font.setSize2(w-8,SCR_HT,17);
    font.setColors(RGBto565(230,230,0),RGBto565(180,180,0),RGBto565(40,40,0));
    font.drawDigit2c(i%10,2*w,0);
    delay(100);
    i++;
  }
}

void demoCounter(int t1,int t2)
{
  lcd.fillScreen(RGBto565(160,160,160));
  font.setColors(RGBto565(40,40,40),RGBto565(140,140,140));
  int w=SCR_WD/6;
  int y1=(SCR_HT/2-w*2)/2;
  int y2=(SCR_HT/2-w*2)/2+SCR_HT/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.setSize1(w-4,w*2,t1);
    for(int i=0;i<6;i++) font.drawDigit1(random(0,10),2+i*w,y1);
    font.setSize2(w-4,w*2,t2);
    for(int i=0;i<6;i++) font.drawDigit2(random(0,10),2+i*w,y2);
    //delay(50);
  }
}

void demoCounterSize1()
{
  lcd.fillScreen(BLACK);
  int mw=SCR_WD/4;
  int t=8;
  int cnt=0;
  for(int i=0;i<12;i++) {
    int w=random(15,mw+1);
    //if(w>21) t=7; else
    //if(w>17) t=6; else
    //if(w>15) t=5; else
    //if(w>12) t=4; else t=3;
    t=w/4;
    font.setSize1(w-4,w*2,t);
    ms=millis();
    int x=random(0,SCR_WD-w*4),y=random(0,SCR_HT-w*2);
    while(millis()-ms<800) {
      font.setColors(MAGENTA,RGBto565(40,0,40));
      font.setSpacing(4);
      snprintf(buf,9,"%04d",cnt);
      font.printNumber1(buf,x,y);
      delay(50);
      cnt+=121;
      if(cnt>9999) cnt=0;
    }
    font.setColors(BLACK,BLACK);
    font.printNumber1(buf,x,y);
  }
}

void demoCounterSize2c()
{
  lcd.fillScreen(BLACK);
  int mw=SCR_WD/4;
  int t=8;
  int cnt=0;
  for(int i=0;i<12;i++) {
    int w=random(15,mw+1);
    //if(w>21) t=7; else
    //if(w>15) t=5; else t=3;
    t=w/4;
    font.setSize2(w-4,w*2,t);
    ms=millis();
    int x=random(0,SCR_WD-w*4),y=random(0,SCR_HT-w*2);
    font.setColors(RGBto565(250,250,250),RGBto565(180,180,180),RGBto565(40,40,40));
    while(millis()-ms<1000) {
      font.setSpacing(4);
      snprintf(buf,9,"%04d",cnt);
      font.printNumber2c(buf,x,y);
      delay(50);
      cnt+=121;
      if(cnt>9999) cnt=0;
    }
    font.setColors(BLACK,BLACK);
    font.printNumber2(buf,x,y);
  }
}

void demoCounterThick1()
{
  lcd.fillScreen(BLACK);
  int w=SCR_WD/3;
  for(int t=5;t<17;t++) {
    font.setSize1(w-8,w*2,t);
    ms=millis();
    font.setColors(RED,RGBto565(50,0,0));
    while(millis()-ms<500) {
      for(int i=0;i<3;i++) font.drawDigit1(random(0,10),i*w,(SCR_HT-w*2)/2);
      delay(50);
    }
    font.setColors(0,0);
    for(int i=0;i<3;i++) font.drawDigit1(8,i*w,(SCR_HT-w*2)/2);
  }
}

void demoCounterThick2()
{
  lcd.fillScreen(BLACK);
  int w=SCR_WD/3;
  for(int t=5;t<=21;t+=2) {
    font.setSize2(w-8,w*2,t);
    ms=millis();
    font.setColors(GREEN,RGBto565(0,40,0));
    while(millis()-ms<500) {
      for(int i=0;i<3;i++) font.drawDigit2(random(0,10),i*w,(SCR_HT-w*2)/2);
      delay(100);
    }
    font.setColors(0,0);
    for(int i=0;i<3;i++) font.drawDigit2(8,i*w,(SCR_HT-w*2)/2);
  }
}

void demoCounterThick2c()
{
  lcd.fillScreen(BLACK);
  int w=SCR_WD/3;
  for(int t=5;t<=25;t+=2) {
    font.setSize2(w-8,w*2,t);
    ms=millis();
    font.setColors(RGBto565(0,240,240),RGBto565(0,180,180),RGBto565(0,40,40));
    while(millis()-ms<600) {
      for(int i=0;i<3;i++) font.drawDigit2c(random(0,10),i*w,(SCR_HT-w*2)/2);
      delay(100);
    }
    font.setColors(0,0,0);
    for(int i=0;i<3;i++) font.drawDigit2c(8,i*w,(SCR_HT-w*2)/2);
  }
}


void demoFloat()
{
  lcd.fillScreen(BLACK);
  lcd.fillRect(0,2*SCR_HT/3,SCR_WD,SCR_HT/3,RGBto565(150,150,150));
  int w=SCR_WD/7;
  long v=-99999;
  ms=millis();
  font.setSpacing(6);
  while(millis()-ms<5000) {
    dtostrf((float)v/100.0,7,2,buf);
    font.setColors(RED,RGBto565(60,0,0));
    font.setSize1(w-4,w*2,7);
    font.printNumber1(buf,4,0);

    font.setColors(GREEN,RGBto565(0,50,0));
    font.setSize2(w-4,w*2,7);
    font.printNumber2(buf,4,w*2+15);

    font.setColors(RGBto565(30,30,30),RGBto565(130,130,130));
    font.setSize2(w-4,w*2,7);
    font.printNumber2(buf,4,w*4+30);
    v+=4901;
    if(v>999999) v=-99999;
    //delay(50);
  }
}

void loop() 
{
  demoBig();

  demoClock1(10);
  demoClock2(11);
  demoClock2c(13);
  
  demoCounter(9,9);

  demoCounterSize1();
  demoCounterSize2c();

  demoCounterThick1();
  demoCounterThick2();
  demoCounterThick2c();

  demoFloat();
}

