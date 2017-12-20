#include "window.h"
#include "game.h"
#include <cstdio>
#include <string>
#include <iostream>

int *pixels = new int[WIDTH * HEIGHT];

void startLoop()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * RECT_SIZE, HEIGHT * RECT_SIZE, SDL_WINDOW_OPENGL);

	SDL_ShowWindow(window);
	SDL_RaiseWindow(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	bool running = true;

	while (running)
	{
		// Event handling...
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
                
                if(e.key.keysym.sym == SDLK_RIGHT) direction_press(KEY_RIGHT);
                else if(e.key.keysym.sym == SDLK_LEFT) direction_press(KEY_LEFT);
                else if(e.key.keysym.sym == SDLK_UP) direction_press(KEY_UP);
                else if(e.key.keysym.sym == SDLK_DOWN) direction_press(KEY_DOWN);
			}
		}

		// game....

		for (int i = 0; i < WIDTH * HEIGHT; i++) pixels[i] = 0;
		render();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		// rendering...
		for (int i = 0; i < WIDTH * HEIGHT; i++)
		{
			int c = pixels[posToIndex(i % WIDTH, i / WIDTH)];
			SDL_SetRenderDrawColor(renderer, (c >> 16) & 0xFF, (c >> 8) & 0xFF, (c & 0xFF), 0xFF);
			SDL_Rect rect = { (int)(i % WIDTH) * RECT_SIZE, (int)(i / WIDTH) * RECT_SIZE, RECT_SIZE, RECT_SIZE };
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
	}
}
