//
//  ThoLib.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 20.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

#include <stdio.h>
#include "ThoLib.h"
#include <iostream>

arduino teensy;

void setup()
{
    std::cout << "Setting up arduino..." << std::endl;
    teensy = openArduino();
    
    writeInt(0xDDCCBBAA);
    while(readArduino(teensy) != 0x0A) usleep(10000);
}

void writeInt(int a)
{
    for(int i = 0; i < 4; i++)
    {
        writeArduino(teensy, a >> (8 * i));
    }
}

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int color)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            drawPixel(x + j, y + i, color);
        }
    }
}

void drawVerticalLine(uint8_t x, uint8_t y, uint8_t length, int color)
{
    for (int i = y; i < y + length; i++) drawPixel(x, i, color);
}

void drawHorizontalLine(uint8_t x, uint8_t y, uint8_t length, int color)
{
    for (int i = x; i < x + length; i++) drawPixel(i, y, color);
}
