// DigiFont library example
// All styles on ST7789 IPS display
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

char buf[20],buf2[10];
long long v=-99999;
unsigned long ms,demoTime=10000;

void setup(void) 
{
  Serial.begin(9600);
  lcd.init(SCR_WD,SCR_HT);
  lcd.fillScreen(BLACK);
}

void style7()
{
  int x=0,y=0,hi=9,ht=44,w=24,h=40;
  lcd.fillScreen(BLACK);
  digi.setSpacing(2);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(1);

  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,3)"); y+=hi;
  //digi.setColors(RGBto565(250,50,250),RGBto565(200,20,200),RGBto565(40,0,40));
  digi.setColors(RGBto565(0,250,250),RGBto565(0,190,190),RGBto565(0,40,40));
  digi.setSize7(24,40,7,3);
  x=digi.printNumber7("23:45",x,y); x=digi.printNumber7("6.78'C",x+10,y);
  y+=ht; x=0;

  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,2)"); y+=hi;
  digi.setColors(RGBto565(250,50,250),RGBto565(190,20,190),RGBto565(60,0,60));
  digi.setSize7(24,40,7,2);
  x=digi.printNumber7("23:45",x,y); x=digi.printNumber7("6.78'C",x+10,y);
  y+=ht; x=0;

  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,0)"); y+=hi;
  //digi.setColors(RGBto565(50,250,50),RGBto565(0,40,0));
  digi.setColors(RGBto565(250,0,0),RGBto565(80,0,0));
  digi.setSize7(24,40,7,0);
  x=digi.printNumber7("23:45",x,y); x=digi.printNumber7("6.78'C",x+10,y);
  y+=ht; x=0;

  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,1)"); y+=hi;
  digi.setSize7(24,40,7,1);
  x=digi.printNumber7("23:45",x,y); x=digi.printNumber7("6.78'C",x+10,y);
  y+=ht; x=0;

  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,2)"); y+=hi;
  digi.setSize7(24,40,7,2);
  x=digi.printNumber7("23:45",x,y); x=digi.printNumber7("6.78'C",x+10,y);
  y+=ht; x=0;

  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,3)"); y+=hi;
  digi.setSize7(24,40,7,3);
  x=digi.printNumber7("23:45",x,y); x=digi.printNumber7("6.78'C",x+10,y);
  y+=ht; x=0;

  delay(demoTime);
}

void style7var()
{
  int x=0,y=0,ht=44+9,hi=44+9;
  lcd.fillScreen(BLACK);
  digi.setSpacing(2);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(1);
  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,3)"); y+=hi;
  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,2)"); y+=hi;
  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,0)"); y+=hi;
  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,1)"); y+=hi;
  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,2)"); y+=hi;
  lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,3)"); y+=hi;

  ms = millis();
  while(millis()-ms<demoTime) {
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    y=9;
    digi.setColors(RGBto565(0,250,250),RGBto565(0,190,190),RGBto565(0,40,40));
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    digi.setSize7(24,40,7,3); digi.printNumber7(buf,x,y); y+=ht;
    digi.setColors(RGBto565(250,50,250),RGBto565(200,20,200),RGBto565(40,0,40));
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    digi.setSize7(24,40,7,2); digi.printNumber7(buf,x,y); y+=ht;

    digi.setColors(RGBto565(50,250,50),RGBto565(0,40,0));
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    digi.setSize7(24,40,7,0); digi.printNumber7(buf,x,y); y+=ht;
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    digi.setSize7(24,40,7,1); digi.printNumber7(buf,x,y); y+=ht;
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    digi.setSize7(24,40,7,2); digi.printNumber7(buf,x,y); y+=ht;
    v=(long)random(60000)*random(60000);    snprintf(buf,20,"%10ld",v);  buf[6]='.';
    digi.setSize7(24,40,7,3); digi.printNumber7(buf,x,y); y+=ht;
    delay(500);
  }
}

void all()
{
  int x=0,y=0,hi=10,ht=45,h,m,t;
  lcd.fillScreen(BLACK);
  digi.setSpacing(2);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(1);

  snprintf(buf,20,"23:45");
  snprintf(buf2,10,"67.8'C");

  ms = millis();
  while(millis()-ms<demoTime*3/2) {
    x=y=0;
  
    lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,3); printNumber7();"); y+=hi;
    //digi.setColors(RGBto565(250,50,250),RGBto565(200,20,200),RGBto565(40,0,40));
    digi.setColors(RGBto565(0,250,250),RGBto565(0,190,190),RGBto565(0,40,40));
    digi.setSize7(24,40,7,3);
    x=digi.printNumber7(buf,x,y); x=digi.printNumber7(buf2,x+10,y);
    y+=ht; x=0;
  
    lcd.setCursor(0,y); lcd.println("setSize7(24,40,7,2); printNumber7();"); y+=hi;
    digi.setSize7(24,40,7,2);
    digi.setColors(RGBto565(250,0,0),RGBto565(80,0,0));
    x=digi.printNumber7(buf,x,y); x=digi.printNumber7(buf2,x+10,y);
    y+=ht; x=0;
    /*
    lcd.setCursor(0,y); lcd.println("setSize3(24,40,7,2); printNumber3();"); y+=hi;
    digi.setSize3(24,40,7);
    digi.setColors(RGBto565(250,0,0),RGBto565(60,0,0));
    x=digi.printNumber3(buf,x,y); x=digi.printNumber3(buf2,x+10,y);
    y+=ht; x=0;
    */
    lcd.setCursor(0,y); lcd.println("setSizeF(24,40,6); printNumberF();"); y+=hi;
    digi.setColors(RGBto565(0,250,0),RGBto565(0,40,0));
    digi.setSizeF(24,40,6);
    x=digi.printNumberF(buf,x,y); x=digi.printNumberF(buf2,x+10,y);
    y+=ht; x=0;
  
    lcd.setCursor(0,y); lcd.println("setSizeO(24,40,6); printNumberO();"); y+=hi;
    digi.setColors(RGBto565(250,250,0),RGBto565(0,0,0));
    digi.setSizeO(24,40,6);
    x=digi.printNumberO(buf,x,y); x=digi.printNumberO(buf2,x+10,y);
    y+=ht; x=0;
  
    lcd.setCursor(0,y); lcd.println("setSizeO/F(24,40,6); printNumberF/O();"); y+=hi;
    digi.setSizeO(24,40,6);
    digi.setColors(RGBto565(0,140,0),BLACK);
    x=digi.printNumberF(buf,x,y); x=digi.printNumberF(buf2,x+10,y);
    digi.setClearBg(0);
    digi.setColors(RGBto565(160,230,0),BLACK);
    x=0;
    x=digi.printNumberO(buf,x,y); x=digi.printNumberO(buf2,x+10,y);
    digi.setClearBg(1);
    y+=ht; x=0;
  
    lcd.setCursor(0,y); lcd.println("setSizeF(16,24,4); printNumberFr();"); y+=hi;
    y+=5; x=5;
    digi.setFrame(5,5);
    digi.setColors(RGBto565(200,200,200),RGBto565(50,50,50));
    digi.setSizeF(16,24,4);
    x=digi.printNumberFr(buf,x,y); x=digi.printNumberFr(buf2,x+20,y);

    h=random(24);
    m=random(60);
    t=random(999);
    snprintf(buf,20,"%02d:%02d",h,m);
    snprintf(buf2,10,"%03d.'C",t);
    buf2[3]=buf2[2]; buf2[2]='.';
    while(millis()-ms<demoTime*1/2);
    delay(800);
  }
}

void loop() 
{
  all();
  style7();
  style7var();
}

