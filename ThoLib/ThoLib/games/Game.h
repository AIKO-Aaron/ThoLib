//
//  Game.hpp
//  ThoLib
//
//  Created by Aaron Hodel on 20.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

/**
 
 ################
 HOW TO ADD GAMES
 ################
 
 1. Create new class in here --> copy preset and rename it to the name of your game
 2. Create implementation in new .cpp (Don't forget to add to compiled files)
 3. Functions to implement:
    - setupGame() --> called once at instantiation of game
    - render() --> called every 1/60th of a second to render
    - direction_press(dir) --> Gets called when a direction was pressed (Use constants KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT)
    - a_press() --> Called when a was pressed
    - b_press() --> Called when b was pressed
 
 ##################
 HOW TO START GAMES
 ##################
 
 1. Instantiate game (Game *g = new Game();), where new Game() is replaced with the name of your game (i.e. new Tetris();)
 2. Call g->run();
 3. Current thread gets blocked... To stop game set g->running = false (probably in game or in another thread)
 
*/

#ifndef Game_h
#define Game_h

#define SPEED_MOD 1

#include "../ThoLib.h"
#include "../Input.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>

// Position is a vector --> store x & y
typedef struct pos
{
    int x, y;
} pos;
static int timer; // A timer (for convinience in the games, because they all have a global timer variable)
static int lastDir = 0;

class Game
{
public:
    bool running = false;
    
    virtual void setupGame() = 0;
    virtual void render() = 0;
    virtual void direction_press(int dir) = 0;
    virtual void a_press() = 0;
    virtual void b_press() = 0;
    
    // Run the game --> 60Hz clock
    void run()
    {
        running = true;
        int frames = 0;
	while(running)
        {
	    if(frames++ >= 60) {
	        frames = 0;
	        std::cout << "Second" << std::endl;
	    }
            std::clock_t start = clock();
            double duration;
            // std::cout << "Hello World" << std::endl;
            userInput input = getUserInput();
            if(input.direction_press != lastDir && input.direction_press != -1) direction_press(input.direction_press);
            lastDir = input.direction_press;
	    if(input.a_press) a_press();
            if(input.b_press) b_press();

            //clearScreen();
            render();
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            usleep(SPEED_MOD * 1000000 / 60 - duration / 1000); // Sleep for 1000/60 milliseconds (60 hertz) & don't wait the time we needed to render & do calculations
            // usleep(1);
	    //read();
	    // std::cout << running << std::endl;
        }
    }
};

// Game definitions

/**
 Preset:
 
 class <NAME> : public Game
 {
 void render() override;
 void direction_press(int dir) override;
 void setupGame() override {}
 void a_press() override {}
 void b_press() override {}
 };
 
 */

class Snake : public Game
{
    void render() override;
    void direction_press(int dir) override;
    
    
    // unused...
    void setupGame() override;
    void a_press() override {}
    void b_press() override {}
};

class Tetris : public Game
{
    void setupGame() override;
    void render() override;
    void direction_press(int dir) override;
    void a_press() override;
    void b_press() override;
};

class Flappy : public Game
{
    void setupGame() override;
    void render() override;
    void direction_press(int dir) override;
    void a_press() override;
    void b_press() override;
};

#endif /* Game_h */
