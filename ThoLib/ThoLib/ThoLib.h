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

void setup(); // Set arduino up

void clearScreen();
void reset();

void read();

void writeInt(int a); // Write an integer to the arduino

inline void drawPixel(uint8_t x, uint8_t y, int color) // Inline function --> convert position & color to single int & write it
{
    color &= 0x00FFFFFF; // Clear alpha bit
    color |= (x & 0x0F) << 24 | (y & 0x0F) << 28;
    writeInt(color);
}

inline void sendCommand(int cmd)
{
    cmd |= 0xFF << 24; // Set command bits
    writeInt(cmd);
}

void drawVerticalLine(uint8_t x, uint8_t y, uint8_t length, int color); // Draw a vertical line
void drawHorizontalLine(uint8_t x, uint8_t y, uint8_t length, int color); // Draw a horizontal line

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int color); // fill a rectangle

#endif /* ThoLib_h */
