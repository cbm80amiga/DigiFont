// ST7789 library example
// flash mem usage
// (c) 2020 Pawel A. Hernik

/*
 ST7789 240x240 IPS (without CS pin) connections (only 6 wires required):

 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/PA5/SCK
 #04 SDA -> D11/PA7/MOSI
 #05 RES -> D9 /PA0 or any digital
 #06 DC  -> D10/PA1 or any digital
 #07 BLK -> NC
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#if (__STM32F1__) // bluepill
#define TFT_DC    PA1
#define TFT_RST   PA0
//#include <Arduino_ST7789_STM.h>
#else
#define TFT_DC    10
#define TFT_RST   9
#include <Arduino_ST7789_Fast.h>
#endif

#define SCR_WD 240
#define SCR_HT 240
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

// -----------
#define USE_RRE  0
#define USE_PROP 0
#define USE_DIGI 1
// -----------


#if USE_RRE==1
#include "RREFont.h"
#include "rre_term_10x16.h"
RREFont rre;
void customRectRRE(int x, int y, int w, int h, int c) { return lcd.fillRect(x, y, w, h, c); }  
#endif

#if USE_PROP==1
#include "PropFont.h"
#include "term8x14_font.h"
PropFont font;
void customPixel(int x, int y, int c) { lcd.drawPixel(x, y, c); }
void customRect(int x, int y, int w, int h, int c) { lcd.fillRect(x, y, w, h, c); } 
#endif

#if USE_DIGI==1
#include "DigiFont.h"
void customLineH(int x0,int x1, int y, int c) { lcd.drawFastHLine(x0,y,x1-x0+1,c); }
void customLineV(int x, int y0,int y1, int c) { lcd.drawFastVLine(x,y0,y1-y0+1,c); } 
void customRectD(int x, int y,int w,int h, int c) { lcd.fillRect(x,y,w,h,c); } 
DigiFont digi(customLineH,customLineV,customRectD);
#endif


//-----------------------------------------------------------------------------
/*
  Memory tests - Arduino IDE 1.6.5
  Empty, only lcd.fillScreen(BLUE)
    8932
  RRE + term 10x16
    16524   7592b
  RRE + term 10x16 ENABLE_RRE_16B only
    12354   3422b
  Prop + term 8x14PL (288 bytes for PL)
    13160
  Digi 1:   10508  1576b
  Digi 2:   10330  1398b
  Digi 2c:  10560  1628b
  Digi 3:   10160  1228b (7seg rect) 
  Digi 4:   11992  3060b (fill)    
  Digi 5:   14198  5266b (outline) 
  Digi 7:   10722 ----  (7seg utlimate old)
  Digi 7:   10770  1838b(7seg utlimate with 2 colors)
*/

#define RGBIto565(r,g,b,i) ((((((r)*(i))/255) & 0xF8) << 8) | ((((g)*(i)/255) & 0xFC) << 3) | ((((b)*(i)/255) & 0xFC) >> 3)) 

void setup() 
{
  Serial.begin(9600);
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(RGBto565(80,0,80));
  
  #if USE_RRE==1
  rre.init(customRectRRE, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values 
  rre.setFont(&rre_term_10x16);
  rre.setScale(2);
  rre.setColor(YELLOW);
  rre.printStr(10,10,"Test");
  #endif

  #if USE_PROP==1
  font.init(customPixel, customRect, SCR_WD, SCR_HT); // custom drawPixel and fillRect function and screen width and height values
  font.setFont(Term8x14PL); 
  font.setScale(2);
  font.setSpacing(2);
  font.setColor(YELLOW);
  font.printStr(10,50,"Test");
  #endif

  #if USE_DIGI==1
  digi.setColors(RGBIto565(250,250,50,255),RGBIto565(250,250,50,180),RGBIto565(250,250,50,50));
  //digi.setColors(RGBIto565(250,250,50,255),RGBIto565(250,250,50,50));
  digi.setSpacing(4);

  //digi.setSize1(50,100,13);
  //digi.setSize2(50,100,13);
  //digi.setSize3(50,100,13);
  //digi.setSize4(50,100,13); //digi.setClearBg(0);  // obsolete
  //digi.setSize5(50,100,13); //digi.setClearBg(0);  // obsolete
  //digi.setSizeF(50,100,13); //digi.setClearBg(0);
  //digi.setSizeO(50,100,13); //digi.setClearBg(0);
  digi.setSize7(50,100,13,6);

  //digi.printNumber1("1234",10,120);
  //digi.printNumber2("1234",10,120);
  //digi.printNumber2c("1234",10,120);
  //digi.printNumber3("1234",10,120);
  //digi.printNumber4("1234",10,120);  // obsolete
  //digi.printNumber5("1234",10,120);  // obsolete
  //digi.printNumberF("1234",10,120);
  //digi.printNumberO("1234",10,120);
  digi.printNumber7("1284",10,120);
  //digi.setSize2(50,100,13);  digi.printNumber2c("1284",10,0);
  #endif
}


void loop()
{
}

