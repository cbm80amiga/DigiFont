// DigiFont library example
// Temperature display on HX1230 LCD
// (c) 2020 Pawel A. Hernik

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
  int w=29,h=52,y=8,t=7;
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
  int w=21,h=50,y=9,t=5;
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

