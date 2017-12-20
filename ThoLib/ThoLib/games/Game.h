//
//  Game.hpp
//  ThoLib
//
//  Created by Aaron Hodel on 20.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "../ThoLib.h"
#include <stdio.h>
#include <iostream>
#include <vector>

typedef struct pos
{
    int x, y;    
} pos;
static int timer;

class Game
{
public:
    virtual void setupGame() = 0;
    virtual void render() = 0;
    virtual void direction_press(int dir) = 0;
    virtual void a_press() = 0;
    virtual void b_press() = 0;
};

class Snake : public Game
{
    void render() override;
    void direction_press(int dir) override;
    
    
    // unused...
    void setupGame() override {}
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

#endif /* Game_h */
