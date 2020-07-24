# DigiFont
Library for nice, scalable digits rendering using any Arduino GFX libraries 

YouTube video:

https://youtu.be/X6PjfhcNE98


## Features
- very fast rendering even on AVR Arduino
- no bitmap data is necessary - only rendering routines
- each number can have different width, height and segment thickness
- should work with any Arduino graphic library with user defined callbacks for drawLine() and fillRect()
- 3 styles of 7-segment font variation
- extra pseudo 3D look for color displays (style 2c)
- simple fast rectangular and outline styles
- each digit only cleans the necessary segments, so cleaning and refreshing the entire screen is not necessary (important for good performance on high definition LCD displays)
- examples for monochrome HX1230 and color ST7789 IPS
- each style has separate methods/functions to save program memory
- if necessary only 3-4 functions can be used separately (setSize,drawSeg,drawDigit,printNumber) without the library
- special look - multi layer rendering is possible: https://youtu.be/OPq9aBJP-pc

If you find it useful and want to buy me a coffee or a beer:

https://www.paypal.me/cbm80amiga
