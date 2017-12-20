#include "window.h"
#include <math.h>

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

void fillEllipse(int x, int y, int a, int b, int color)
{
    for (int i = -a; i <= a; i++)
    {
        for (int j = -b; j <= b; j++)
        {
            if((float) (j * j) / (float)(a * a) + (float)(i * i) / (float)(b * b) <= 1) drawPixel(x + j, y + i, color);
        }
    }
}


void drawRect(int x, int y, int w, int h, int color)
{
    w -= 1;
    h -= 1;
    
    for (int i = 0; i <= h; i++)
    {
        drawPixel(x, y + i, color);
        drawPixel(x + w, y + i, color);
    }
    for (int j = 0; j < w; j++)
    {
        drawPixel(x + j, y, color);
        drawPixel(x + j, y + h, color);
    }
}

void drawEllipse(int x, int y, int a, int b, int color)
{
    for (int i = -a; i <= a; i++)
    {
        for (int j = -b; j <= b; j++)
        {
            float c = (float) (j * j) / (float)(a * a) + (float)(i * i) / (float)(b * b);
            if(c <= 1.0 && c >= 0.5 / sqrt(a * a + b * b)) drawPixel(x + j, y + i, color);
        }
    }
}
