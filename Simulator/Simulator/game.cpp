#include "game.h"
#include <iostream>

float x = 0;

void render()
{
	fillRect((uint8_t) x & 0xFF, 3, 2, 3, 0xFFFFFF);
	x += 0.1;
}