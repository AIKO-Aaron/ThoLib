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

#define KEY_RIGHT 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_UP 3

#define WIDTH 15
#define HEIGHT 10

void setup();

void writeInt(int a);
void writePixel(uint8_t x, uint8_t y, int color);

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int color);

#endif /* ThoLib_h */
