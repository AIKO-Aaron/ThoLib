#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "util.h"
#include <iostream>

#define WIDTH 15
#define HEIGHT 10
#define RECT_SIZE 60

#define KEY_RIGHT 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_UP 3

static inline uint8_t posToIndex(uint8_t x, uint8_t y)
{
	return y * WIDTH + (y % 2 == 1 ? WIDTH - x - 1 : x);
}

static SDL_Window *window;
static SDL_Renderer *renderer;

void startLoop();

#endif
