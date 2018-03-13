#include "../game.h"
#include <iostream>
#include <vector>

typedef struct {
    int x, y;
} pos;

int timer = 0;

#define TIME 20/6

pos foodpos;
int direction = 0;
std::vector<pos> currentSnake;

void setupGame()
{
    foodpos = { rand() % WIDTH, rand() % HEIGHT };
    direction = 0;
    currentSnake = std::vector<pos>();
}

void render()
{
    while(currentSnake.size() < 4) {
        currentSnake.push_back({ WIDTH / 2, HEIGHT / 2 });
    }
    
    for(int i = 0; i < currentSnake.size(); i++)
    {
        drawPixel(currentSnake[i].x, currentSnake[i].y, 0xFF00FF);
    }
    
    if(timer++ >= TIME)
    {
        timer = 0;
        for(int i = (int) currentSnake.size() - 1; i > 0; i--)
        {
            if(currentSnake[i].x == currentSnake[0].x && currentSnake[i].y == currentSnake[0].y && (currentSnake.size() > 4 && currentSnake.size() - 1 != i))
            {
                currentSnake.clear();
                direction = 0;
            }
            currentSnake[i] = currentSnake[i - 1];
        }
        currentSnake[0].x += direction == KEY_RIGHT ? 1 : direction == KEY_LEFT ? -1 : 0;
        currentSnake[0].y += direction == KEY_DOWN ? 1 : direction == KEY_UP ? -1 : 0;
        
        if(currentSnake[0].x < 0 || currentSnake[0].x >= WIDTH || currentSnake[0].y < 0 || currentSnake[0].y >= HEIGHT)
        {
            currentSnake.clear();
            direction = 0;
        }
        
        if(foodpos.x == currentSnake[0].x && foodpos.y == currentSnake[0].y)
        {
            currentSnake.push_back({currentSnake[0].x, currentSnake[0].y});
            foodpos = { rand() % WIDTH, rand() % HEIGHT };
        }
    }
    
    drawPixel(foodpos.x, foodpos.y, 0xFF0000);
}

void direction_press(int dir)
{
    if(direction % 2 == dir % 2 && direction != dir)
    {
        currentSnake.clear();
        direction = 0;
    }
    direction = dir;
}

void a_press() {}
void b_press() {}

