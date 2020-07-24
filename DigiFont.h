// 7-segment and outline digit font rendering library
// (c) 2020 by Pawel A. Hernik

#ifndef _DIGI_FONT_H
#define _DIGI_FONT_H 

// ---------------------------------
class DigiFont {
public:
  DigiFont(void (*_linehFun)(int x0,int x1, int y, int c),
           void (*_linevFun)(int x, int y0,int y1, int c),
           void (*_rectFun)(int x, int y,int w, int h, int c));
  void init(void (*_linehFun)(int x0,int x1, int y, int c),
            void (*_linevFun)(int x, int y0,int y1, int c),
            void (*_rectFun)(int x, int y,int w, int h, int c));

  // separate for each style to save program memory
  void drawSeg1(int seg, int x, int y, int c);
  void drawSeg2(int seg, int x, int y, int c);
  void drawSeg2c(int seg, int x, int y, int c);
  void drawSeg3(int seg, int x, int y, int c);
  void setSize1(int wd, int ht, int th);
  void setSize2(int wd, int ht, int th);
  void setSize3(int wd, int ht, int th);
  void setSize4(int wd, int ht, int th);
  void setSize5(int wd, int ht, int th);
  int drawDigit1(int ch, int x, int y);
  int drawDigit2(int ch, int x, int y);
  int drawDigit2c(int ch, int x, int y);
  int drawDigit3(int ch, int x, int y);
  int drawDigit4(int ch, int x, int y);
  int drawDigit5(int ch, int x, int y);
  int printNumber1(char *txt, int x, int y);
  int printNumber2(char *txt, int x, int y);
  int printNumber2c(char *txt, int x, int y);
  int printNumber3(char *txt, int x, int y);
  int printNumber4(char *txt, int x, int y);
  int printNumber5(char *txt, int x, int y);
  void clear45(int ch, int x, int y);

  // common for all styles
  void setSegment(int wd, int ht, int th);
  void setSpacing(int sp) { spacing = sp; }
  void setClearBg(int cl) { clearBg = cl; }
  void setColors(int c1, int c0) { colOn=colOn2=c1; colOff=c0; }
  void setColors(int c1, int c2, int c0) { colOn=c1; colOn2=c2; colOff=c0; }
  int getWidth() { return digWd; }
  int getHeight() { return digHt; }
  int numberWidth(char *txt);
  void rect(int x, int y, int w, int h, int col);

  // callbacks
  void (*linehFun)(int x0,int x1, int y, int c);
  void (*linevFun)(int x, int y0,int y1, int c);
  void (*rectFun)(int x, int y,int w, int h, int c);

  int digWd, digHt;
  int segWd, segHt;
  int segThick;
  int colOn,colOn2,colOff;
  int spacing;
  int clearBg;
};
#endif

