// DigiFont library example
// Demo on HX1230 LCD
// (c) 2020 Pawel A. Hernik
// YouTube video: https://youtu.be/X6PjfhcNE98

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
char buf[20];

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

void demoClock3(int t)
{
  int w=21;
  font.setSize3(w-1,40,t);
  int y=(SCR_HT-40)/2;
  ms=millis();
  while(millis()-ms<4000) {
    lcd.cls();
    font.drawDigit3(random(0,3),0*w,y);
    font.drawDigit3(random(0,4),1*w,y);
    font.drawDigit3(':',1+2*w,y);
    font.drawDigit3(random(0,6),t+3+2*w,y);
    font.drawDigit3(random(0,10),t+3+3*w,y);
    lcd.display();
    delay(600);
  }
}

void demoClock5(int t)
{
  int w=21;
  font.setSize5(w-2,40,t);
  int y=(SCR_HT-40)/2;
  ms=millis();
  while(millis()-ms<5000) {
    lcd.cls();
    font.drawDigit5(random(0,3),0*w,y);
    font.drawDigit5(random(0,4),1*w,y);
    font.drawDigit5(':',1+2*w,y);
    font.drawDigit5(random(0,6),t+3+2*w,y);
    font.drawDigit5(random(0,10),t+3+3*w,y);
    lcd.display();
    delay(600);
  }
}

void demoBig()
{
  lcd.cls();
  int i=0;
  int w=SCR_WD/3;
  ms=millis();
  while(millis()-ms<6000) {
    font.setSize1(w-2,SCR_HT,5);
    font.drawDigit1(i,0*w,0);
    font.setSize2(w-2,SCR_HT,5);
    font.drawDigit2(i,1*w,0);
    font.setSize5(w-2,SCR_HT,10);
    font.drawDigit5(i,2*w,0);
    lcd.display();
    delay(300);
    if(++i>9) i=0;
  }
}

void demoCounter(int t1,int t2)
{
  lcd.cls();
  font.setColors(1,0);
  int w=SCR_WD/6;
  int y1=(SCR_HT/2-w*2)/2;
  int y2=(SCR_HT/2-w*2)/2+SCR_HT/2;
  ms=millis();
  while(millis()-ms<5000) {
    font.setSize1(w-2,w*2,t1);
    for(int i=0;i<6;i++) font.drawDigit1(random(0,10),2+i*w,y1);
    font.setSize2(w-2,w*2,t2);
    for(int i=0;i<6;i++) font.drawDigit2(random(0,10),2+i*w,y2);
    lcd.display();
    delay(200);
  }
}

void demoCounterSize1()
{
  lcd.cls();
  int mw=SCR_WD/4;
  int t,cnt=0;
  for(int i=0;i<10;i++) {
    int w=random(10,mw+1);
    t=w/4;
    font.setSize1(w-2,w*2,t);
    font.setSpacing(2);
    ms=millis();
    int x=random(0,SCR_WD-w*4),y=random(0,SCR_HT-w*2);
    font.setColors(1,0);
    while(millis()-ms<800) {
      snprintf(buf,9,"%04d",cnt);
      font.printNumber1(buf,x,y);
      lcd.display();
      delay(150);
      cnt+=121;
      if(cnt>9999) cnt=0;
    }
    font.setColors(0,0);
    font.printNumber1(buf,x,y);
    lcd.display();
  }
}

void demoCounterSize2()
{
  lcd.cls();
  int mw=SCR_WD/4;
  int t,cnt=0;
  for(int i=0;i<10;i++) {
    int w=random(10,mw+1);
    t=w/4;
    font.setSize2(w-2,w*8/5,t);
    font.setSpacing(2);
    ms=millis();
    int x=random(0,SCR_WD-w*4),y=random(0,SCR_HT-w*2);
    font.setColors(1,0);
    while(millis()-ms<800) {
      snprintf(buf,9,"%04d",cnt);
      font.printNumber2(buf,x,y);
      lcd.display();
      delay(150);
      cnt+=121;
      if(cnt>9999) cnt=0;
    }
    font.setColors(0,0);
    font.printNumber2(buf,x,y);
    lcd.display();
  }
}

void demoCounterSize5()
{
  lcd.cls();
  int mw=SCR_WD/4;
  int t,cnt=0;
  for(int i=0;i<10;i++) {
    int w=random(10,mw+1);
    t=w/3;
    font.setSize5(w-2,w*2,t);
    font.setSpacing(2);
    ms=millis();
    int x=random(0,SCR_WD-w*4),y=random(0,SCR_HT-w*2);
    font.setColors(1,0);
    while(millis()-ms<800) {
      lcd.cls();
      snprintf(buf,9,"%04d",cnt);
      font.printNumber5(buf,x,y);
      lcd.display();
      delay(150);
      cnt+=121;
      if(cnt>9999) cnt=0;
    }
    //font.setColors(0,0);
    //font.printNumber2(buf,x,y);
    //lcd.display();
  }
}

void demoCounterThick1(int numdig)
{
  lcd.cls();
  int w=SCR_WD/numdig;
  for(int t=3;t<=10;t++) {
    font.setSize1(w-2,SCR_HT,t);
    ms=millis();
    font.setColors(1,0);
    while(millis()-ms<900) {
      for(int i=0;i<numdig;i++) font.drawDigit1(random(0,10),i*w,0);
      lcd.display();
      delay(200);
    }
    font.setColors(0,0);
    for(int i=0;i<numdig;i++) font.drawDigit1(8,i*w,0);
    lcd.display();
  }
}

void demoCounterThick2(int numdig)
{
  lcd.cls();
  int w=SCR_WD/numdig;
  for(int t=3;t<=11;t+=2) {
    font.setSize2(w-2,SCR_HT,t);
    ms=millis();
    font.setColors(1,0);
    while(millis()-ms<900) {
      for(int i=0;i<numdig;i++) font.drawDigit2(random(0,10),i*w,0);
      lcd.display();
      delay(200);
    }
    font.setColors(0,0);
    for(int i=0;i<numdig;i++) font.drawDigit2(8,i*w,0);
    lcd.display();
  }
}

void demoCounterThick3(int numdig)
{
  lcd.cls();
  int w=SCR_WD/numdig;
  for(int t=3;t<9;t++) {
    font.setSize3(w-2,SCR_HT,t);
    ms=millis();
    font.setColors(1,0);
    while(millis()-ms<900) {
      for(int i=0;i<numdig;i++) font.drawDigit3(random(0,10),i*w,0);
      lcd.display();
      delay(200);
    }
    font.setColors(0,0);
    for(int i=0;i<numdig;i++) font.drawDigit3(8,i*w,0);
    lcd.display();
  }
}

void demoCounterThick4(int numdig)
{
  lcd.cls();
  int w=SCR_WD/numdig;
  for(int t=3;t<13;t++) {
    font.setSize4(w-4,SCR_HT,t);
    ms=millis();
    font.setColors(1,0);
    while(millis()-ms<900) {
      for(int i=0;i<numdig;i++) font.drawDigit4(random(0,10),i*w,0);
      lcd.display();
      delay(200);
    }
    font.setColors(0,0);
    for(int i=0;i<numdig;i++) font.drawDigit4(8,i*w,0);
    lcd.display();
  }
}

void demoCounterThick5(int numdig)
{
  lcd.cls();
  int w=SCR_WD/numdig;
  for(int t=4;t<13;t++) {
    font.setSize3(w-4,SCR_HT,t);
    ms=millis();
    font.setColors(1,0);
    while(millis()-ms<900) {
      for(int i=0;i<numdig;i++) font.drawDigit5(random(0,10),i*w,0);
      lcd.display();
      delay(200);
    }
    font.setColors(0,0);
    for(int i=0;i<numdig;i++) font.drawDigit5(8,i*w,0);
    lcd.display();
  }
}

void demoFloat()
{
  lcd.cls();
  font.setColors(1,0);
  int w=14;
  int h=21;
  long v=-99999;
  ms=millis();
  font.setSpacing(2);
  while(millis()-ms<5000) {
    dtostrf((float)v/100.0,7,2,buf);
    font.setSize1(w-2,h,3);
    font.printNumber1(buf,4,0);

    font.setSize2(w-2,h,3);
    font.printNumber2(buf,4,h+2);

    font.setSize5(w-2,h,4);
    font.printNumber5(buf,4,h*2+4);
    lcd.display();
    v+=4901;
    if(v>999999) v=-99999;
    delay(150);
  }
}

void loop() 
{
  demoBig();

  demoClock1(5);
  demoClock2(5);
  demoClock3(5);
  demoClock5(7);

  demoCounter(3,3);

  demoCounterSize1();
  demoCounterSize2();
  demoCounterSize5();

  demoCounterThick1(3);
  demoCounterThick2(3);
  demoCounterThick3(3);
  demoCounterThick4(3);
  demoCounterThick5(3);

  ///demoCounterThick1(2);
  ///demoCounterThick2(2);
  demoCounterThick3(2);
  demoCounterThick4(2);
  demoCounterThick5(2);

  demoFloat();
}

