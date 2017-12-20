#include "game.h"
#include <iostream>

float x = 0;

void render()
{
	fillEllipse(5, 3, 5, 5, 0xFFFFFF);
	x += 0.1;
}
