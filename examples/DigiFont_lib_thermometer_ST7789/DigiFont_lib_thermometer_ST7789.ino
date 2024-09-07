// DigiFont library example
// Temperature display on ST7789 IPS
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
}

unsigned long ms,demoTime=5000;
char buf[20];

float readIntTemp() 
{
  long result;
  // Read temperature sensor against 1.1V reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = (result - 125) * 1075;
  return result/10000.0;
}

void show2_1()
{
  int w=50,h=90,x=0,y=75,t=13;
  lcd.fillScreen(BLACK);
  digi.setColors(RGBto565(250,0,250),RGBto565(200,0,200),RGBto565(40,0,40));
  digi.setSize7(w-2,h,t,t/2);
  digi.setSpacing(4);
  ms=millis();
  while(millis()-ms<demoTime) {
    float temp=readIntTemp();
    dtostrf(temp,2,1,buf);
    x=digi.printNumber7(buf,x,y);
    x=digi.printNumber7("'C",x+8,y);
    delay(300);
  }
}

void loop() 
{
  show2_1();
}

