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
}

void writeInt(int a)
{
    for(int i = 0; i < 4; i++)
    {
        writeArduino(teensy, a >> (8 * i));
    }
}

inline void writePixel(uint8_t x, uint8_t y, int color)
{
    color &= 0x00FFFFFF; // Clear alpha bit
    color |= (x & 0x0F) << 24 | (y & 0x0F) << 28;
    writeInt(color);
}

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int color)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            writePixel(x + j, y + i, color);
        }
    }
}
