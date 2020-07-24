// 7-segment and outline digit font rendering library
// (c) 2020 by Pawel A. Hernik

#include "DigiFont.h"

// ----------------------------------------------------------------
DigiFont::DigiFont(void (*_linehFun)(int x0,int x1, int y, int c),
                   void (*_linevFun)(int x, int y0,int y1, int c),
                   void (*_rectFun)(int x, int y,int w, int h, int c))
{
  init(_linehFun,_linevFun,_rectFun);
  setSize1(10,20,5);
  setColors(1,0);
  spacing = 1;
  clearBg = 1;
}
// ----------------------------------------------------------------
// linehFun,_linevFun and rectFun callbacks are necessary to initialize the library
void DigiFont::init(void (*_linehFun)(int x0,int x1, int y, int c),
                    void (*_linevFun)(int x, int y0,int y1, int c),
                    void (*_rectFun)(int x, int y,int w, int h, int c))
{
  linehFun = _linehFun;
  linevFun = _linevFun;
  rectFun  = _rectFun;
}

void DigiFont::setSize1(int wd, int ht, int th)
{
  digWd = wd;
  digHt = ht;
  segThick = th;
  segWd = wd-2;
  segHt = (ht-3)/2;
  //Serial.print(segWd); Serial.print("x"); Serial.println(segHt);
}

void DigiFont::setSize2(int wd, int ht, int th)
{
  digWd = wd;
  digHt = ht;
  segThick = th;
  segWd = wd-th/2-th/2-2;
  segHt = (ht-th-2)/2;
  //Serial.print(segWd); Serial.print("x"); Serial.println(segHt);
}

void DigiFont::setSize3(int wd, int ht, int th)
{
  digWd = wd;
  digHt = ht;
  segThick = th;
  //segWd = wd-th*2;
  //segHt = (ht-th*3)/2;
  segWd = wd-th*2-2;
  segHt = (ht-th/2-th/2)/2-1;
  //Serial.print(segWd); Serial.print("x"); Serial.println(segHt);
}

void DigiFont::setSize4(int wd, int ht, int th)
{
  digWd = wd;
  digHt = ht;
  segThick = th;
  segWd = wd;
  segHt = (ht-th*3)/2;
  //Serial.print(segWd); Serial.print("x"); Serial.println(segHt);
}

void DigiFont::setSize5(int wd, int ht, int th)
{
  digWd = wd;
  digHt = ht;
  segThick = th;
  segWd = wd;
  segHt = (ht-th*3)/2;
  //Serial.print(segWd); Serial.print("x"); Serial.println(segHt);
}

void DigiFont::setSegment(int wd, int ht, int th)
{
  segThick = th;
  segWd = wd;
  segHt = ht; 
}

void DigiFont::drawSeg1(int seg, int x, int y, int c)
{
  if(!c && !clearBg) return;
  int i,ofs=segThick/2;
  switch(seg) {
    case 0: // top
      for(i=0;i<segThick;i++) (*linehFun)(x+i,x+segWd-1-i, y+i, c ? colOn : colOff);
      break;
    case 3: // bottom
      for(i=0;i<segThick;i++) (*linehFun)(x+i,x+segWd-1-i, y+segThick-1-i, c ? colOn : colOff);
      break;
    case 6: // middle
      for(i=0;i<1+ofs;i++) (*linehFun)(x+i,x+segWd-1-i,y+ofs-i, c ? colOn : colOff);
      for(i=1;i<1+ofs;i++) (*linehFun)(x+i,x+segWd-1-i,y+ofs+i, c ? colOn : colOff);
      break;
    case 4: // left
    case 5: // left
      for(i=0;i<segThick;i++) (*linevFun)(x+i, y+i,y+segHt-1-i, c ? colOn : colOff);
      break;
    case 1: // right
    case 2: // right
      for(i=0;i<segThick;i++) (*linevFun)(x+segThick-1-i, y+i,y+segHt-1-i, c ? colOn : colOff);
      break;
  }
}

void DigiFont::drawSeg2(int seg, int x, int y, int c)
{
  if(!c && !clearBg) return;
  int i,ofs=segThick/2;
  switch(seg) {
    case 0: // top
    case 3: // bottom
    case 6: // middle
      for(i=0;i<ofs+1;i++) (*linehFun)(x+i,x+segWd-1-i, y+ofs-i, c ? colOn : colOff);
      for(i=1;i<ofs+1;i++) (*linehFun)(x+i,x+segWd-1-i, y+ofs+i, c ? colOn : colOff);
      break;
    case 1: // right
    case 2: // right
    case 4: // left
    case 5: // left
      for(i=0;i<ofs+1;i++) (*linevFun)(x+ofs-i, y+i,y+segHt-1-i, c ? colOn : colOff);
      for(i=1;i<ofs+1;i++) (*linevFun)(x+ofs+i, y+i,y+segHt-1-i, c ? colOn : colOff);
      break;
  }
}

void DigiFont::drawSeg2c(int seg, int x, int y, int c)
{
  if(!c && !clearBg) return;
  int i,ofs=segThick/2;
  switch(seg) {
    case 0: // top
    case 3: // bottom
    case 6: // middle
      for(i=0;i<ofs+1;i++) (*linehFun)(x+i,x+segWd-1-i, y+ofs-i, c ? colOn  : colOff);
      for(i=1;i<ofs+1;i++) (*linehFun)(x+i,x+segWd-1-i, y+ofs+i, c ? colOn2 : colOff);
      break;
    case 1: // right
    case 2: // right
    case 4: // left
    case 5: // left
      for(i=0;i<ofs+1;i++) (*linevFun)(x+ofs-i, y+i,y+segHt-1-i, c ? colOn  : colOff);
      for(i=1;i<ofs+1;i++) (*linevFun)(x+ofs+i, y+i,y+segHt-1-i, c ? colOn2 : colOff);
      break;
  }
}

void DigiFont::drawSeg3(int seg, int x, int y, int c)
{
  if(!c && !clearBg) return;
  int i,ofs=segThick/2;
  switch(seg) {
    case 0: // top
    case 3: // bottom
    case 6: // middle
      (*rectFun)(x,y, segWd,segThick, c ? colOn : colOff);
      break;
    case 1: // right
    case 2: // right
    case 4: // left
    case 5: // left
      (*rectFun)(x,y, segThick,segHt, c ? colOn : colOff);
      break;
  }
}

/*
 Segment bits:
   00
  5  1
  5  1
   66
  4  2
  4  2
   33
*/

static unsigned char digits[10]={
  0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111};

int DigiFont::drawDigit1(int ch, int x, int y)
{
  int s;
  switch(ch) {
    case '.':
      (*rectFun)(x,y+segHt+segHt+3-segThick,segThick,segThick,colOn); return segThick;
    case ':':  
      //(*rectFun)(x,y+1+(segHt-segThick)/2,segThick,segThick,colOn);
      //(*rectFun)(x,y+segHt+2+(segHt-segThick)/2,segThick,segThick,colOn);
      (*rectFun)(x,y+      2+(segHt-segThick)/2,segThick,segThick,colOn);
      (*rectFun)(x,y+segHt+1+(segHt-segThick)/2,segThick,segThick,colOn);
      return segThick; 
    case ' ':
      s=0; break;
    case '-':
      s=0b1000000; break;
    default:
      s=digits[ch&0xf];
  }
  drawSeg1(0,x+1,               y+0,                       s&0b0000001);
  drawSeg1(1,x+segWd+2-segThick,y+1,                       s&0b0000010);
  drawSeg1(2,x+segWd+2-segThick,y+segHt+2,                 s&0b0000100);
  drawSeg1(3,x+1,               y+segHt+2+segHt-segThick+1,s&0b0001000);
  drawSeg1(4,x+0,               y+segHt+2,                 s&0b0010000);
  drawSeg1(5,x+0,               y+1,                       s&0b0100000);
  drawSeg1(6,x+1,               y+segHt-segThick/2+1,      s&0b1000000);
  return digWd; 
}

int DigiFont::drawDigit2(int ch, int x, int y)
{
  int s,ofs=1+segThick/2;
  switch(ch) {
    case '.':
      (*rectFun)(x,y+segHt+segHt+2,segThick,segThick,colOn); return segThick;
    case ':':
      //(*rectFun)(x,y+ofs+(segHt-segThick)/2,segThick,segThick,colOn);
      //(*rectFun)(x,y+segHt+1+ofs+(segHt-segThick)/2,segThick,segThick,colOn);
      (*rectFun)(x,y+      1+ofs+(segHt-segThick)/2,segThick,segThick,colOn);
      (*rectFun)(x,y+segHt+1+ofs+(segHt-segThick)/2,segThick,segThick,colOn);
      return segThick; 
    case ' ':
      s=0; break;
    case '-':
      s=0b1000000; break;
    default:
      s=digits[ch&0xf];
  }
  drawSeg2(0,x+ofs,     y+0,            s&0b0000001);
  drawSeg2(1,x+segWd+1, y+ofs,          s&0b0000010);
  drawSeg2(2,x+segWd+1, y+ofs+segHt+1,  s&0b0000100);
  drawSeg2(3,x+ofs,     y+segHt+segHt+2,s&0b0001000);
  drawSeg2(4,x+0,       y+ofs+segHt+1,  s&0b0010000);
  drawSeg2(5,x+0,       y+ofs,          s&0b0100000);
  drawSeg2(6,x+ofs,     y+segHt+1,      s&0b1000000);
  return digWd; 
}

int DigiFont::drawDigit2c(int ch, int x, int y)
{
  int s,ofs=1+segThick/2;
  switch(ch) {
    case '.':
      (*rectFun)(x,y+segHt+segHt+2,segThick,segThick,colOn);
      (*rectFun)(x,y+segHt+segHt+2+segThick/2,segThick,segThick-segThick/2,colOn2);
      return segThick;
    case ':':
      (*rectFun)(x,y+ofs+(segHt-segThick)/2,segThick,segThick/2,colOn);
      (*rectFun)(x,y+ofs+(segHt-segThick)/2+segThick/2,segThick,segThick-segThick/2,colOn2);
      (*rectFun)(x,y+segHt+1+ofs+(segHt-segThick)/2,segThick,segThick,colOn);
      (*rectFun)(x,y+segHt+1+ofs+(segHt-segThick)/2+segThick/2,segThick,segThick-segThick/2,colOn2);
      return segThick; 
    case ' ':
      s=0; break;
    case '-':
      s=0b1000000; break;
    default:
      s=digits[ch&0xf];
  }
  drawSeg2c(0,x+ofs,     y+0,            s&0b0000001);
  drawSeg2c(1,x+segWd+1, y+ofs,          s&0b0000010);
  drawSeg2c(2,x+segWd+1, y+ofs+segHt+1,  s&0b0000100);
  drawSeg2c(3,x+ofs,     y+segHt+segHt+2,s&0b0001000);
  drawSeg2c(4,x+0,       y+ofs+segHt+1,  s&0b0010000);
  drawSeg2c(5,x+0,       y+ofs,          s&0b0100000);
  drawSeg2c(6,x+ofs,     y+segHt+1,      s&0b1000000);
  return digWd; 
}

int DigiFont::drawDigit3(int ch, int x, int y)
{
  int s,ofs=segThick/2;
  switch(ch) {
    case '.':
      (*rectFun)(x,y+digHt-1-segThick,segThick,segThick,colOn); return segThick;
    case ':':
      //(*rectFun)(x,y+segThick+(segHt-segThick)/2,segThick,segThick,colOn);
      //(*rectFun)(x,y+segHt+segThick*2+(segHt-segThick)/2,segThick,segThick,colOn);
      (*rectFun)(x,y+(digHt/2-segThick)/2+1,segThick,segThick,colOn);
      (*rectFun)(x,y+digHt-1-(digHt/2-segThick)/2-segThick-1,segThick,segThick,colOn);
      return segThick;
    case ' ':
      s=0; break;
    case '-':
      s=0b1000000; break;
    default:
      s=digits[ch&0xf];
  }
  /*  
  drawSeg3(0,x+segThick,       y+0,                  s&B0000001);
  drawSeg3(1,x+segThick+segWd, y+segThick,           s&B0000010);
  drawSeg3(2,x+segThick+segWd, y+segThick*2+segHt,   s&B0000100);
  drawSeg3(3,x+segThick,       y+(segThick+segHt)*2, s&B0001000);
  drawSeg3(4,x+0,              y+segThick*2+segHt,   s&B0010000);
  drawSeg3(5,x+0,              y+segThick,           s&B0100000);
  drawSeg3(6,x+segThick,       y+segThick+segHt,     s&B1000000);
  */
  drawSeg3(0,x+segThick+1,       y+0,                 s&0b0000001);
  drawSeg3(1,x+segThick+segWd+2, y+ofs,               s&0b0000010);
  drawSeg3(2,x+segThick+segWd+2, y+digHt-1-ofs-segHt, s&0b0000100);
  drawSeg3(3,x+segThick+1,       y+digHt-1-segThick,  s&0b0001000);
  drawSeg3(4,x+0,                y+digHt-1-ofs-segHt, s&0b0010000);
  drawSeg3(5,x+0,                y+ofs,               s&0b0100000);
  drawSeg3(6,x+segThick+1,       y+(digHt-segThick)/2,s&0b1000000);
  return digWd; 
}

void DigiFont::clear45(int ch, int x, int y)
{
  int hc=(digHt-segThick*3)/2;
  switch(ch) {
    case ' ':
      (*rectFun)(x,y,   digWd,digHt,colOff);
      break;
    case '-':
      (*rectFun)(x,y,               digWd,hc+segThick,colOff);
      (*rectFun)(x,y+hc+segThick*2, digWd,digHt-hc-segThick*2,colOff);
      break;
    case 0:
      (*rectFun)(x+segThick,y+hc+segThick,   digWd-segThick*2,segThick,colOff);
      break;
    case 1:
      (*rectFun)(x,         y,               segThick,digHt,colOff);
      (*rectFun)(x+segThick,y,               digWd-segThick*2,segThick,colOff);
      (*rectFun)(x+segThick,y+hc+segThick,   digWd-segThick*2,segThick,colOff);
      (*rectFun)(x+segThick,y+digHt-segThick,digWd-segThick*2,segThick,colOff);
      break;
    case 2:
      (*rectFun)(x,               y+segThick,      segThick,hc,colOff);
      (*rectFun)(x+digWd-segThick,y+segThick*2+hc,segThick,digHt-hc-segThick*3,colOff);
      break;
    case 3:
      (*rectFun)(x,         y+segThick,      segThick,digHt-segThick*2,colOff);
      break;
    case 4:
      (*rectFun)(x,         y+segThick*2+hc,  segThick,digHt-segThick*2-hc,colOff);
      (*rectFun)(x+segThick,y,                digWd-segThick*2,segThick,colOff);
      (*rectFun)(x+segThick,y+digHt-segThick, digWd-segThick*2,segThick,colOff);
      break;
    case 5:
      (*rectFun)(x+digWd-segThick,y+segThick,     segThick,hc,colOff);
      (*rectFun)(x,               y+segThick*2+hc,segThick,digHt-hc-segThick*3,colOff);
      break;
    case 6:
      (*rectFun)(x+digWd-segThick,y+segThick,       segThick,hc,colOff);
      break;
    case 7:
      (*rectFun)(x,         y+segThick,      segThick,digHt-segThick,colOff);
      (*rectFun)(x+segThick,y+hc+segThick,   digWd-segThick*2,segThick,colOff);
      (*rectFun)(x+segThick,y+digHt-segThick,digWd-segThick*2,segThick,colOff);
      break;
    case 8:
      break;
    case 9:
      (*rectFun)(x,               y+hc+segThick*2,segThick,digHt-hc-segThick*3,colOff);
      break;
  }
}

int DigiFont::drawDigit4(int ch, int x, int y)
{
  int hc=(digHt-segThick*3)/2;
  ch = ch>='0' && ch<='9' ? ch-'0' : ch;
  if(clearBg) clear45(ch,x,y);
  switch(ch) {
    case '.':
      (*rectFun)(x,y+digHt-segThick,segThick,segThick,colOn);
       return segThick;
    case ':':
      (*rectFun)(x,y+(digHt/2-segThick)/2+2,segThick,segThick,colOn);
      (*rectFun)(x,y+digHt-1-(digHt/2-segThick)/2-segThick-1,segThick,segThick,colOn);
      return segThick;
    case ' ':
      break;
    case '-':
      (*rectFun)(x,y+hc+segThick,   digWd,segThick,colOn);
      break;
    case 0:
      (*rectFun)(x,               y,segThick,digHt,colOn);
      (*rectFun)(x+digWd-segThick,y,segThick,digHt,colOn);
      (*rectFun)(x+segThick,y,               digWd-segThick*2,segThick,colOn);
      (*rectFun)(x+segThick,y+digHt-segThick,digWd-segThick*2,segThick,colOn);
      break;
    case 1:
      (*rectFun)(x+digWd-segThick,y,segThick,digHt,colOn);
      break;
    case 2:
      (*rectFun)(x,y,               digWd,segThick,colOn);
      (*rectFun)(x,y+hc+segThick,   digWd,segThick,colOn);
      (*rectFun)(x,y+digHt-segThick,digWd,segThick,colOn);
      (*rectFun)(x,               y+segThick*2+hc,segThick,digHt-hc-segThick*3,colOn);
      (*rectFun)(x+digWd-segThick,y+segThick,     segThick,hc,colOn);
      break;
    case 3:
      (*rectFun)(x,y,               digWd-segThick,segThick,colOn);
      //(*rectFun)(x+segThick,y+hc+segThick,   digWd-segThick*1,segThick,colOn);
      //(*rectFun)(x,y+hc+segThick,   digWd-segThick,segThick,colOn); // full width
      (*rectFun)(x+digWd/3,y+hc+segThick,   digWd-segThick-digWd/3,segThick,colOn); // 2/3 width
      (*rectFun)(x,y+digHt-segThick,digWd-segThick,segThick,colOn);
      (*rectFun)(x+digWd-segThick,y,         segThick,digHt,colOn);
      break;
    case 4:
      (*rectFun)(x+digWd-segThick,y,             segThick,digHt,colOn);
      (*rectFun)(x,               y,             segThick,hc+segThick*2,colOn);
      (*rectFun)(x+segThick,      y+hc+segThick, digWd-segThick*2,segThick,colOn);
      //(*rectFun)(x+digWd-segThick,y+segThick,         segThick,digHt-segThick,colOn);
      //(*rectFun)(x,y,         segThick,hc+segThick*3,colOn);
      //(*rectFun)(x+segThick,y+hc+segThick*2,   digWd-segThick*2,segThick,colOn);
      break;
    case 5:
      (*rectFun)(x,y,               digWd,segThick,colOn);
      (*rectFun)(x,y+hc+segThick,   digWd,segThick,colOn);
      (*rectFun)(x,y+digHt-segThick,digWd,segThick,colOn);
      (*rectFun)(x,               y+segThick,     segThick,hc,colOn);
      (*rectFun)(x+digWd-segThick,y+segThick*2+hc,segThick,digHt-hc-segThick*3,colOn);
      break;
    case 6:
      (*rectFun)(x,y,                      digWd,segThick,colOn);
      (*rectFun)(x+segThick,y+hc+segThick, digWd-segThick,segThick,colOn);
      (*rectFun)(x,y+digHt-segThick,       digWd,segThick,colOn);
      (*rectFun)(x,               y+segThick,       segThick,digHt-segThick*2,colOn);
      (*rectFun)(x+digWd-segThick,y+hc+segThick*2,  segThick,digHt-hc-segThick*3,colOn);
      break;
    case 7:
      (*rectFun)(x+digWd-segThick,y,segThick,      digHt,colOn);
      (*rectFun)(x,               y,digWd-segThick,segThick,colOn);
      break;
    case 8:
      (*rectFun)(x,               y,segThick,digHt,colOn);
      (*rectFun)(x+digWd-segThick,y,segThick,digHt,colOn);
      (*rectFun)(x+segThick,y,               digWd-segThick*2,segThick,colOn);
      (*rectFun)(x+segThick,y+digHt-segThick,digWd-segThick*2,segThick,colOn);
      (*rectFun)(x+segThick,y+hc+segThick,            digWd-segThick*2,segThick,colOn);
      break;
    case 9:
      (*rectFun)(x,               y,                segThick,hc+segThick*2,colOn);
      (*rectFun)(x+digWd-segThick,y,                segThick,digHt,colOn);
      (*rectFun)(x+segThick,      y,                digWd-segThick*2,segThick,colOn);
      (*rectFun)(x+segThick,      y+hc+segThick,    digWd-segThick*2,segThick,colOn);
      (*rectFun)(x,               y+digHt-segThick, digWd-segThick,segThick,colOn);
      break;
  }
  return digWd; 
}

void DigiFont::rect(int x, int y, int w, int h, int col)
{
  (*linehFun)(x, x+w-1, y+h-1,col);
  (*linehFun)(x, x+w-1, y,    col);
  (*linevFun)(x,    y+1, y+h-2,col);
  (*linevFun)(x+w-1,y+1, y+h-2,col);
}

int DigiFont::drawDigit5(int ch, int x, int y)
{
  int hc=(digHt-segThick*3)/2;
  ch = ch>='0' && ch<='9' ? ch-'0' : ch;
  if(clearBg) {
    clear45(ch,x,y);
    // cleaning up leftover after previous digits
    (*rectFun)(x+1,y+1, segThick-1,segThick-1,colOff);
    (*rectFun)(x+digWd-segThick,y+1, segThick-1,segThick-1,colOff);
    (*rectFun)(x+digWd-segThick,y+digHt-segThick, segThick-1,segThick-1,colOff);
    (*rectFun)(x+digWd-segThick,y+hc+segThick, segThick-1,segThick,colOff);
    (*rectFun)(x+1,y+hc+segThick, segThick-1,segThick,colOff);
    (*rectFun)(x+1,y+digHt-segThick, segThick-1,segThick-1,colOff);
    (*linevFun)(x+segThick, y+segThick+hc+1,    y+segThick+hc+1+segThick-2, colOff); // le-mid-short '3'
    (*linehFun)(x+1,x+segThick-1, y+digHt-segThick, colOff); // bot-left
  }
  switch(ch) {
    case '.':
      rect(x,y+digHt-segThick,segThick,segThick,colOn);
       return segThick;
    case ':':
      rect(x,y+(digHt/2-segThick)/2+2,segThick,segThick,colOn);
      rect(x,y+digHt-1-(digHt/2-segThick)/2-segThick-1,segThick,segThick,colOn);
      return segThick;
    case ' ':
      break;
    case '-':
      rect(x,y+hc+segThick,   digWd,segThick,colOn);
      break;
    case 0:
      rect(x,y,digWd,digHt,colOn);
      rect(x+segThick-1,y+segThick-1,digWd-segThick*2+2,digHt-segThick*2+2,colOn);
      break;
    case 1:
      rect(x+digWd-segThick,y,segThick,digHt,colOn);
      break;
    case 2:
      (*linehFun)(x,          x+digWd-1,        y,  colOn); // top
      (*linehFun)(x,          x+digWd-segThick, y+segThick-1,  colOn); // top2
      (*linehFun)(x,          x+digWd-1,        y+digHt-1,  colOn); // bottom
      (*linehFun)(x+segThick, x+digWd-1,        y+digHt-segThick,  colOn); // bottom2
      (*linehFun)(x,          x+digWd-segThick, y+segThick+hc,  colOn); // mid
      (*linehFun)(x+segThick, x+digWd-1,        y+segThick+hc+segThick-1,  colOn); // mid2
      (*linevFun)(x+digWd-1,        y+1,               y+hc+segThick*2-1, colOn); // rt
      (*linevFun)(x+digWd-segThick, y+segThick-1,       y+hc+segThick, colOn); // rt le
      (*linevFun)(x,                y+hc+segThick+1,    y+digHt-2, colOn); // le
      (*linevFun)(x+segThick-1,     y+hc+segThick*2-1,  y+digHt-segThick, colOn); // le rt
      (*linevFun)(x,                y+1,                y+segThick-2, colOn); // le short
      (*linevFun)(x+digWd-1,        y+digHt-segThick+1, y+digHt-2, colOn); // rt short
      break;
    case 3:
      (*linehFun)(x,          x+digWd-1,        y,  colOn); // top
      (*linehFun)(x,          x+digWd-1,        y+digHt-1,  colOn); // bottom
      (*linehFun)(x,          x+digWd-segThick, y+segThick-1,  colOn); // top2
      (*linehFun)(x,          x+digWd-segThick, y+digHt-segThick,  colOn); // bottom2
      //(*linehFun)(x+segThick, x+digWd-segThick, y+segThick+hc,  colOn); // mid1
      //(*linehFun)(x+segThick, x+digWd-segThick, y+segThick*2+hc-1,  colOn); // mid2
      //(*linehFun)(x, x+digWd-segThick, y+segThick+hc,  colOn); // mid1 full width
      //(*linehFun)(x, x+digWd-segThick, y+segThick*2+hc-1,  colOn); // mid2 full width
      (*linehFun)(x+digWd/3, x+digWd-segThick, y+segThick+hc,  colOn); // mid1 2/3 width
      (*linehFun)(x+digWd/3, x+digWd-segThick, y+segThick*2+hc-1,  colOn); // mid2 2/3 width
      (*linevFun)(x+digWd-1,  y+1,                y+digHt-2, colOn); // rt-long
      (*linevFun)(x,          y+1, y+segThick-2, colOn); // le-top-short
      (*linevFun)(x,          y+digHt-segThick+1, y+digHt-2, colOn); // le-bot-short
      //(*linevFun)(x+segThick, y+segThick+hc+1,    y+segThick+hc+1+segThick-2, colOn); // le-mid-short
      //(*linevFun)(x, y+segThick+hc+1,    y+segThick+hc+1+segThick-2, colOn); // le-mid-short full width
      (*linevFun)(x+digWd/3-1, y+segThick+hc+0,    y+segThick+hc+1+segThick-2, colOn); // le-mid-short 2/3 width
      (*linevFun)(x+digWd-segThick,  y+segThick,           y+segThick+1+hc-1, colOn); //le-top
      (*linevFun)(x+digWd-segThick,  y+segThick*2+hc,      y+segThick*2+hc+1+hc-1, colOn); //le-bot
      break;
    case 4:
      (*linehFun)(x,                  x+segThick-1,     y, colOn); // top short1
      (*linehFun)(x+digWd-segThick,   x+digWd-1,        y, colOn); // top short2
      (*linehFun)(x+digWd-segThick,   x+digWd-1,        y+digHt-1,  colOn); // bottom short
      (*linehFun)(x+segThick,         x+digWd-segThick, y+segThick+hc,  colOn); // mid1
      (*linehFun)(x,                  x+digWd-segThick, y+segThick+hc+segThick-1,  colOn); // mid2      
      (*linevFun)(x+digWd-1,         y+1,             y+digHt-2, colOn); // rt-long
      (*linevFun)(x+digWd-segThick,  y+1,             y+segThick+hc-1, colOn); //rt-left-top
      (*linevFun)(x+digWd-segThick,  y+hc+segThick*2, y+digHt-2, colOn); //rt-left-bot
      (*linevFun)(x,                 y+1,             y+segThick*2+hc-1, colOn); //le-le
      (*linevFun)(x+segThick-1,      y+1,             y+segThick+hc, colOn); //le-rt
      break;
    case 5:
      (*linehFun)(x,          x+digWd-1,        y,  colOn); // top
      (*linehFun)(x+segThick, x+digWd-1,        y+segThick-1,  colOn); // top2
      (*linehFun)(x,          x+digWd-1,        y+digHt-1,  colOn); // bottom
      (*linehFun)(x,          x+digWd-segThick, y+digHt-segThick,  colOn); // bottom2
      (*linehFun)(x+segThick, x+digWd-1,        y+segThick+hc,  colOn); // mid
      (*linehFun)(x,          x+digWd-segThick, y+segThick+hc+segThick-1,  colOn); // mid2
      (*linevFun)(x,                y+1,             y+hc+segThick*2-1, colOn); // le
      (*linevFun)(x+segThick-1,     y+segThick-1,    y+hc+segThick, colOn); // le rt
      (*linevFun)(x+digWd-1,        y+hc+segThick+1, y+digHt-2, colOn); // rt
      (*linevFun)(x+digWd-segThick, y+hc+segThick*2, y+digHt-segThick-1, colOn); // rt le
      (*linevFun)(x+digWd-1,        y+1,             y+segThick-2, colOn); // rt short
      (*linevFun)(x,                y+digHt-segThick+1, y+digHt-2, colOn); // le short
      break;
    case 6:
      rect(x+segThick-1,y+hc+segThick*2-1,digWd-segThick*2+2,digHt-hc-segThick*3+2,colOn);
      (*linehFun)(x,          x+digWd-1, y,  colOn); // top
      (*linehFun)(x+segThick, x+digWd-1, y+segThick-1,  colOn); // top2
      (*linehFun)(x,          x+digWd-1, y+digHt-1,  colOn); // bottom
      (*linehFun)(x+segThick, x+digWd-1, y+segThick+hc,  colOn); // mid
      (*linevFun)(x,            y+1, y+digHt-2, colOn); // le long
      (*linevFun)(x+segThick-1, y+segThick-1, y+hc+segThick, colOn); // le rt
      (*linevFun)(x+digWd-1,    y+hc+segThick+1, y+digHt-2, colOn); // rt
      (*linevFun)(x+digWd-1,    y+1, y+segThick-2, colOn); // rt short
      break;
    case 7:
      (*linehFun)(x,                x+digWd-1,          y,  colOn); // top
      (*linehFun)(x+digWd-segThick, x+digWd-1,          y+digHt-1,  colOn); // bottom
      (*linehFun)(x,                x+digWd-1-segThick, y+segThick-1,  colOn); // bottom2
      (*linevFun)(x+digWd-1,        y+1,                y+digHt-2, colOn); // rt-long
      (*linevFun)(x,                y+1,                y+segThick-2, colOn);  // le-short
      (*linevFun)(x+digWd-segThick, y+segThick-1,       y+digHt-1, colOn); // rt-le-long
      break;
    case 8:
      rect(x,y,digWd,digHt,colOn);
      rect(x+segThick-1,y+segThick-1,     digWd-segThick*2+2,hc+2,colOn);
      rect(x+segThick-1,y+hc+segThick*2-1,digWd-segThick*2+2,digHt-hc-segThick*3+2,colOn);
      break;
    case 9:
      rect(x+segThick-1,y+segThick-1, digWd-segThick*2+2,hc+2,colOn);
      (*linehFun)(x, x+digWd-1, y, colOn); // top
      (*linehFun)(x, x+digWd-1, y+digHt-1, colOn); // bot
      (*linehFun)(x, x+digWd-1-segThick, y+segThick*2+hc-1,  colOn); // mid
      (*linehFun)(x, x+digWd-1-segThick, y+digHt-segThick,  colOn); // bot-higher
      (*linevFun)(x+digWd-1,        y+1, y+digHt-2, colOn); // rt-long
      (*linevFun)(x,                y+1, y+hc+segThick*2-2, colOn);  // le-top
      (*linevFun)(x,                y+digHt-segThick+1, y+digHt-2, colOn); // le-bot-short
      (*linevFun)(x+digWd-segThick, y+hc+segThick*2-1, y+digHt-segThick, colOn); // rt-le-bot
      break;
  }
  return digWd; 
}

int DigiFont::printNumber1(char *txt, int x, int y)
{
  while(*txt) x+=drawDigit1(*txt++,x,y)+spacing;
  return x-spacing;
}

int DigiFont::printNumber2(char *txt, int x, int y)
{
  while(*txt) x+=drawDigit2(*txt++,x,y)+spacing;
  return x-spacing;
}

int DigiFont::printNumber2c(char *txt, int x, int y)
{
  while(*txt) x+=drawDigit2c(*txt++,x,y)+spacing;
  return x-spacing;
}

int DigiFont::printNumber3(char *txt, int x, int y)
{
  while(*txt) x+=drawDigit3(*txt++,x,y)+spacing;
  return x-spacing;
}

int DigiFont::printNumber4(char *txt, int x, int y)
{
  while(*txt) x+=drawDigit4(*txt++,x,y)+spacing;
  return x-spacing;
}

int DigiFont::printNumber5(char *txt, int x, int y)
{
  while(*txt) x+=drawDigit5(*txt++,x,y)+spacing;
  return x-spacing;
}

int DigiFont::numberWidth(char *txt)
{
  int wd=0;
  while(*txt) { wd+=((*txt=='.' || *txt==':')?segThick:digWd)+spacing; txt++; }
  return wd-spacing;
}

// ---------------------------------
