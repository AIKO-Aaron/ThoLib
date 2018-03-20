#include "window.h"
#include "game.h"
#include <cstdio>
#include <string>
#include <iostream>

int *pixels = new int[WIDTH * HEIGHT];
int lastDir = 0;

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
                	}
                /**
                  TODO implement input....
                 */
		}

        userInput input = {
            
        };//getUserInput();
            	if(lastDir != input.direction_press && input.direction_press != -1) direction_press(input.direction_press);
            	lastDir = input.direction_press;
		if(input.a_press) a_press();
            	if(input.b_press) b_press();

		// game....

		for (int i = 0; i < WIDTH * HEIGHT; i++) pixels[i] = 0; // Clear screen
		render(); // Render stuff

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
