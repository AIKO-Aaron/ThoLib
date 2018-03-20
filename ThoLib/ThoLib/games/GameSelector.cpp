//
//  GameSelector.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 20.03.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "./Game.h"
#include <vector>

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
}

void GameSelector::b_press() {}

void GameSelector::direction_press(int dir) {
    if(dir == KEY_RIGHT) {
        index = (index + 1) % GAME_COUNT;
    }
}
