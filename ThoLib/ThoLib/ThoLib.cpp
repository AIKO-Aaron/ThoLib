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

static arduino teensy; // public arduino variable

void setup()
{
    std::cout << "Setting up arduino..." << std::endl;
    teensy = openArduino(); // Try to open interface to arduino....
    //writeInt(0x30313233); // Write "I'm here, waiting" to arduino
    //writeInt(0x33323130);
    /**while(true) {std::cout << readArduino(teensy);
        writeInt(0x31323334);
        usleep(1000000);
    }*/
    std::cout << "Opening arduino done... Synchronizing" << std::endl;
    std::cout << "Done" << std::endl;
}

void clearScreen()
{
    // std::cout << readArduino(teensy);
    sendCommand(0x00DEAD);
}

void reset()
{
    sendCommand(0xFFFFFF); // -1 --> reset
}

void writeInt(int a)
{
    writeIntArduino(teensy, a);
}

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int color)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            drawPixel(x + j, y + i, color); // For each pixel in the rect --> draw pixel
        }
    }
}

void drawVerticalLine(uint8_t x, uint8_t y, uint8_t length, int color)
{
    if(length <= 0 || length >= HEIGHT) return;
    for (int i = y; i < y + length; i++) drawPixel(x, i, color); // For each pixel in the line --> draw pixel
}

void drawHorizontalLine(uint8_t x, uint8_t y, uint8_t length, int color)
{
    if(length <= 0 || length >= HEIGHT) return;
    for (int i = x; i < x + length; i++) drawPixel(i, y, color); // For each pixel in the line --> draw pixel
}
