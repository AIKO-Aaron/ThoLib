//
//  ThoLib.h
//  ThoLib
//
//  Created by Aaron Hodel on 20.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

#ifndef ThoLib_h
#define ThoLib_h

#include <stdlib.h>
#include "arduino.h"

#define WIDTH 15
#define HEIGHT 10

typedef unsigned char uint8_t;

void setup();

void writeInt(int a);

inline void drawPixel(uint8_t x, uint8_t y, int color)
{
    color &= 0x00FFFFFF; // Clear alpha bit
    color |= (x & 0x0F) << 24 | (y & 0x0F) << 28;
    writeInt(color);
}

void drawVerticalLine(uint8_t x, uint8_t y, uint8_t length, int color);
void drawHorizontalLine(uint8_t x, uint8_t y, uint8_t length, int color);

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int color);

#endif /* ThoLib_h */
