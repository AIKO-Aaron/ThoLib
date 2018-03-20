#include "./Game.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <random>

float seed;

#define SPEED 0.003
#define JUMP_POWER 0.01
#define TIME 60/3
#define PIPE_DISTANCE 7
#define TOP_BOTTOM 4

// Chaos function for random
float chaos(float i)
{
    return 4.0 * i * (1.0 - i);
}

// Set a random seed
void srandom_int(float s)
{
    seed = s / (float) RAND_MAX;
}

// Use seed as starting value & retrieve random value from iterating chaos function
int random_int(int min, int max, int p)
{
    float ret = seed;
    for (int i = 0; i < p; i++)
    {
        ret = chaos(ret);
    }
    return (int)(0xFFFFFF * ret) % max + min;
}


int currentFrontPipe = 0, offset = WIDTH;
float yvelocity = 0, y = HEIGHT / 2;

void Flappy::setupGame()
{
    srand((int) time(NULL));
    srandom_int(rand());
}

void Flappy::render()
{    
    if (++timer >= TIME)
    {
        timer = 0;
        if (--offset < 0)
        {
            offset = PIPE_DISTANCE - 1;
            ++currentFrontPipe;
            std::cout << "Next pipe..." << std::endl;
        }
    }
    bool dead = y < 0 || y >= HEIGHT;
    if (offset == 2)
    {
        int ri = random_int(2, HEIGHT - TOP_BOTTOM, currentFrontPipe);
        if (y < ri || y > ri + 3)
        {
            dead = true;
        }
    }
    
#ifdef UNDYING
    dead = false;
#endif
    std::cout.flush();
    if (dead)
    {
        std::cout << "Dead" << std::endl;
        offset = WIDTH;
        srandom_int(rand());
        y = WIDTH / 2;
        yvelocity = 0;
	// exit(0);
    }
    
    yvelocity += SPEED;
    int yy = y;
    y += yvelocity;
    if(yy = (int)y) return;
    for (int i = offset; i < WIDTH; i += PIPE_DISTANCE)
    {
        int ri = random_int(2, HEIGHT - TOP_BOTTOM, currentFrontPipe + (i - offset) / PIPE_DISTANCE);
        drawVerticalLine(i, 0, ri, 0xFF00FF);
        drawVerticalLine(i, ri + 3, HEIGHT - 3 - ri, 0xFF00FF);
        drawVerticalLine(i, ri, 3, 0xFFFFFF);
    }
    drawPixel(2, y, 0xFFFF00);
}

void Flappy::direction_press(int dir)
{
    // if (dir == KEY_UP) y--;
    // if (dir == KEY_DOWN) y++;
}

void Flappy::a_press()
{
    // jump
    if(yvelocity >= -JUMP_POWER * 10) yvelocity = -JUMP_POWER * 10;
    else yvelocity -= JUMP_POWER;
}

void Flappy::b_press() {}




