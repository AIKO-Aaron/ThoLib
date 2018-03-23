//
//  Snake.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 20.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

#include "./Game.h"

#define TIME (60/6/SPEED_MOD)

pos foodpos = { rand() % WIDTH, rand() % HEIGHT };
int direction = 0;
std::vector<pos> currentSnake = std::vector<pos>();

void Snake::setupGame() {
	drawPixel(foodpos.x, foodpos.y, 0xFF0000);
    clearScreen();
    drawPixel(foodpos.x, foodpos.y, 0xFF0000);
    for(int i = 0; i < currentSnake.size(); i++) clearPixel(currentSnake[i].x, currentSnake[i].y);
    currentSnake.clear();}

bool inSnake(int x, int y) {
	for(int i = 0; i < currentSnake.size(); i++) if(currentSnake[i].x == x && currentSnake[i].y == y) return true;
	return false;
}

void Snake::render()
{
   //clearScreen();

    while(currentSnake.size() < 4) {
        currentSnake.push_back({ WIDTH / 2, HEIGHT / 2 });
    }
/**
    for(int i = 0; i < currentSnake.size(); i++)
    {
	//std::cout << "Drawing pixel..." << std::endl;
        drawPixel(currentSnake[i].x, currentSnake[i].y, 0xFF00FF);
    }
*/
    if(timer++ >= TIME)
    {
       //clearScreen();
       timer = 0;
	clearPixel(currentSnake[currentSnake.size() - 1].x, currentSnake[currentSnake.size() - 1].y);
        for(int i = (int) currentSnake.size() - 1; i > 0; i--)
        {
            if(currentSnake[i].x == currentSnake[0].x && currentSnake[i].y == currentSnake[0].y && (currentSnake.size() > 4 && currentSnake.size() - 1 != i))
            {
                //currentSnake.clear();
                running = false;
                return;
            }
            currentSnake[i] = currentSnake[i - 1];
        }
        currentSnake[0].x += direction == KEY_RIGHT ? 1 : direction == KEY_LEFT ? -1 : 0;
        currentSnake[0].y += direction == KEY_DOWN ? 1 : direction == KEY_UP ? -1 : 0;

        if(currentSnake[0].x < 0 || currentSnake[0].x >= WIDTH || currentSnake[0].y < 0 || currentSnake[0].y >= HEIGHT)
        {
	    //for(int i = 0; i < currentSnake.size(); i++) drawPixel(currentSnake[0].x, currentSnake[i].y, 0);
            //currentSnake.clear();
            running = false;
            return;
        }

        drawPixel(foodpos.x, foodpos.y, 0xFF0000);
	for(int i = 0; i < currentSnake.size(); i++)
    	{
            drawPixel(currentSnake[i].x, currentSnake[i].y, 0xFF00FF);
    	}

        if(foodpos.x == currentSnake[0].x && foodpos.y == currentSnake[0].y)
        {
	    drawPixel(foodpos.x, foodpos.y, 0);
            currentSnake.push_back({currentSnake[0].x, currentSnake[0].y});
            while(inSnake(foodpos.x, foodpos.y)) foodpos = { rand() % WIDTH, rand() % HEIGHT };
	    drawPixel(foodpos.x, foodpos.y, 0xFF0000);
        }
    }
    //std::cout << "Drawing pixels..." << std::endl;
    //drawPixel(foodpos.x, foodpos.y, 0xFF0000);
    //std::cout << "Done..."<<std::endl;
    return;
}

void Snake::direction_press(int dir)
{
    if(direction % 2 == dir % 2 && direction != dir)
    {
	//die();
        //currentSnake.clear();
        //direction = 0;
    } else direction = (dir+1) % 4;
}
