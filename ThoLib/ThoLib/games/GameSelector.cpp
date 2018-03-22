//
//  GameSelector.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 20.03.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "./Game.h"
#include <vector>

<<<<<<< HEAD
#define GAME_COUNT 2

int redraw = true;
int p_index = 0;

void GameSelector::setupGame() {}
void GameSelector::a_press() {}

int pixels[1+GAME_COUNT][150] = {
{   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0, 0xFF0000, 0,
        0, 0, 0, 0, 0xFF00FF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFF00FF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0xFF00FF, 0, 0, 0, 0, 0,
        0, 0, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x00FF00, 0x00FF00, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0x00FF00, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0x00FF00, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFF00FF, 0x0000FF, 0, 0, 0, 0, 0, 0, 0, 0,
        0xFF00FF, 0x0000FF, 0x0000FF, 0, 0, 0, 0, 0, 0, 0xFFFF00,
        0xFF00FF, 0x0000FF, 0x4c4c4c, 0, 0, 0x00FFFF, 0x00FFFF, 0xFFFF00, 0xFFFF00, 0xFFFF00,
        0xFF00FF, 0xFF0000, 0x4c4c4c, 0x4c4c4c, 0, 0x00FFFF, 0x00FFFF, 0xABABAB, 0xABABAB, 0xABABAB,
        0xFF0000, 0xFF0000, 0xFF0000, 0x4c4c4c, 0, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xABABAB},
    
    {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 2, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void GameSelector::render() {
    if(redraw) {
        for(int i = 0; i < 150; i++) {
            drawPixel(i / HEIGHT, i % HEIGHT, pixels[p_index][i]);
	    //std::cout << i << ":" << (i / WIDTH) << std::endl;
	    usleep(40000);
        }
	--redraw;
    }
=======
#define GAME_COUNT 3

void GameSelector::setupGame() {}
void GameSelector::render() {}

void GameSelector::a_press() {
    Game *g;
    switch(index) {
        case 0:
            g = new Snake();
            break;
        case 1:
            g = new Tetris();
            break;
        case 2:
            g = new Flappy();
            break;
        default:
            g = new GameSelector(); // Should never be called....
            break;
    }
    
    running = false;
    g->run();
>>>>>>> 19a7671aded6e1ed5703e36a179abbcdabcd929c
}

void GameSelector::b_press() {}

void GameSelector::direction_press(int dir) {
<<<<<<< HEAD
    if(dir == 0x01) {
        p_index = (p_index + 1) % GAME_COUNT;
        redraw = 1;
    } else if(dir == 2) {
	std::cout << "Starting game: " << p_index << std::endl;
	Game *g;
        switch(p_index) {
            case 0:
                g = new Snake();
                break;
            case 1:
                g = new Tetris();
                break;
            case 2:
                g = new Flappy();
                break;
            default:
                g = new GameSelector(); // Should never be called....
                break;
        }
	clearScreen();
	usleep(1000000);
        g->run();
    }
}

=======
    if(dir == KEY_RIGHT) {
        index = (index + 1) % GAME_COUNT;
    }
}
>>>>>>> 19a7671aded6e1ed5703e36a179abbcdabcd929c
