[![license-badge][]][license] ![version]  ![hit-count] [![github-issues][]][issues]

# DigiFont

A library that allows to render nice, scalable 7-segment digits using the Arduino GFX library.

|All Styles|Style7 Variations|
|--|--|
|<img src="images/allstyles.jpg" title="allstyles" height="400" /> |<img src="images/style7.jpg" title="style7" height="400" />|

YouTube videos:

https://youtu.be/X6PjfhcNE98

https://youtu.be/Z_YCfJZn_bA


## Features
- very fast rendering even on AVR Arduino
- no bitmap data is necessary - only rendering routines
- each number can have different width, height and segment thickness
- should work with any Arduino graphic library with user defined callbacks for drawLine() and fillRect()
- 3 styles of 7-segment font variation
- additional pseudo 3D look for color displays (style 2c)
- simple fast rectangular and outline styles
- each digit clears the necessary segments only, so clearing and refreshing the entire screen is not necessary (important for good performance on high-resolution LCD displays)
- examples for monochrome HX1230, ST7567 and color ST7789 IPS
- each style has separate methods/functions to save program memory
- if necessary only 3-4 functions can be used separately (setSize,drawSeg,drawDigit,printNumber) without the library
- special look with multi-layer rendering is possible: https://youtu.be/OPq9aBJP-pc
- new 7-segment style #7, int which the appearance of the segment can be defined using an additional parameter (can replace styles #1 and #2)

## Last changes
- styles 1 and 2/2c are now obsolete, use them only if you need lower memory usage, use style 7 instead
- style 7 supports now 2 colors similar to style 2c
- setSize7(50,100,13,6) is equivalent for setSize2(50,100,13)
- setSize7(50,100,13,0) is equivalent for setSize1(50,100,13) but setSize7(50,100,13,2) gives better appearance
- style 4 and 5 are renamed to F (filled) and O (outline) but old names left for compatibility
- new feature: setFrame(),printNumberFr() to render simple non-flickering numbers on ony background with a frame around it

## Program memory usage and examples
|Style|Usage|Info|Example|
|--|--|--|--|
|style 1|1650|7-segment style #1|<img src="images/st1.jpg" title="style1" />|
|style 2|1452|7-segment style #2|<img src="images/st2.jpg" title="style2" />|
|style 2c|1714|2-color version for pseudo 3D appearance|<img src="images/st2c.jpg" title="style2c" />|
|style 3|1270|simple rectangle segments for low memory applications|<img src="images/st3.jpg" title="style3" />|
|style F/4|3378|filled|<img src="images/st4.jpg" title="style4" />|
|style Fr|3570|filled, with a frame around|<img src="images/stFr.jpg" title="styleFr" />|
|style O/5|5924|outline|<img src="images/st5.jpg" title="style5" />|
|style 7|1870|versatile replacement for style 1 and 2/2c|<img src="images/st7.jpg" title="style7" />|

If you find it useful and want to buy me a coffee or a beer:

https://buycoffee.to/cbm80

https://www.paypal.me/cbm80amiga

[license-badge]: https://img.shields.io/badge/License-GPLv3-blue.svg
[license]:       https://choosealicense.com/licenses/gpl-3.0/
[version]:       https://img.shields.io/badge/Version-1.1.1-green.svg
[hit-count]:     https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fcbm80amiga%2FDigiFont&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false
[github-issues]: https://img.shields.io/github/issues/cbm80amiga/DigiFont.svg
[issues]:        https://github.com/cbm80amiga/DigiFont/issues/
