#pragma once

#include "window.h"

extern int *pixels;

void drawPixel(int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && pixels != NULL) pixels[posToIndex(x, y)] = color;
}

void fillRect(int x, int y, int w, int h, int color)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			drawPixel(x + j, y + i, color);
		}
	}
}