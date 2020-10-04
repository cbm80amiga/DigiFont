// DigiFont library example
// Temperature display on ST7567 LCD
// (c) 2020 Pawel A. Hernik

/*
 128x64 ST7567 connections in SPI mode (only 5-6 wires between LCD and MCU):

 #01 LED  -> D6, GND or any pin via resistor
 #02 RST  -> D9 or any pin
 #03 CS   -> D10 or any pin
 #04 DC   -> D8 or any pin
 #05 SCK  -> D13/SCK
 #06 SDI  -> D11/MOSI
 #07 3V3  -> VCC (3.3V)
 #08 GND  -> GND
*/

#define LCD_BL  6
#define LCD_CS  10
#define LCD_DC  8
#define LCD_RST 9

#include "ST7567_FB.h"
#include <SPI.h>
ST7567_FB lcd(LCD_DC, LCD_RST, LCD_CS);

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
  digitalWrite(LCD_BL, LOW);
  lcd.init();
  lcd.cls();
  lcd.display();
  font.setColors(1,0);
}

unsigned long ms;
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

void show2()
{
  lcd.cls();
  font.setColors(1,0);
  int w=40,h=64,y=0,t=7;
  ms=millis();
  while(millis()-ms<9000) {
    float temp=readIntTemp();
    dtostrf(temp,2,0,buf);
    font.setSize7(w-2,h,t,2);
    font.drawDigit7(buf[0],w*0,y);
    font.drawDigit7(buf[1],w*1,y);
    lcd.fillRect(w*2,y,t,t,1);
    font.drawDigit7(10+'c'-'a',w*2+t+2,y);
    lcd.display();
    delay(500);
  }
}

void show2_1()
{
  lcd.cls();
  font.setColors(1,0);
  int w=28,h=64,y=0,t=7;
  ms=millis();
  while(millis()-ms<9000) {
    float temp=readIntTemp();
    dtostrf(temp,2,1,buf);
    font.setSize7(w-2,h,t,1);
    font.drawDigit7(buf[0],w*0,y);
    font.drawDigit7(buf[1],w*1,y);
    font.drawDigit7('.',w*2,y);
    font.drawDigit7(buf[3],w*2+t+2,y);
    lcd.fillRect(w*3+t+2,y,t,t,1);
    font.drawDigit7(10+'c'-'a',w*3+(t+2)*2,y);
    lcd.display();
    delay(500);
  }
}

void loop() 
{
  show2();
  show2_1();
}

