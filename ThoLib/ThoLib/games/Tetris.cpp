#include "Game.h"

#define TIME 60 / 2

unsigned int currentIndex = 0;

pos movingBrick[4]; // the moving brick --> all bricks have 4 tiles
unsigned int field[WIDTH * HEIGHT]; // 15 * 10 --> 150 tiles

//utility functions & definitions

int indexToColor(int index)
{
    return ((0x123456 * index) % 0xFFFFFF) | 0x070707;
}

static pos bricks[7][4] = {
    {{WIDTH / 2 - 1, 0}, {WIDTH / 2 - 1, 1}, {WIDTH / 2 - 1, 2}, {WIDTH / 2 - 1, 3}}, // Line
    {{WIDTH / 2 - 1, 0}, {WIDTH / 2 - 1, 1}, {WIDTH / 2 - 1, 2}, {WIDTH / 2, 2}}, // L
    {{WIDTH / 2, 0}, {WIDTH / 2, 1}, {WIDTH / 2, 2}, {WIDTH / 2 - 1, 2}}, // Reverse L
    {{WIDTH / 2 - 1, 0}, {WIDTH / 2, 0}, {WIDTH / 2 + 1, 0}, {WIDTH / 2, 1}}, // T
    {{WIDTH / 2 - 1, 0}, {WIDTH / 2 - 1, 1}, {WIDTH / 2, 1}, {WIDTH / 2, 2}}, // Z
    {{WIDTH / 2, 0}, {WIDTH / 2, 1}, {WIDTH / 2 - 1, 1}, {WIDTH / 2 - 1, 2}}, // S
    {{WIDTH / 2 - 1, 0}, {WIDTH / 2, 0}, {WIDTH / 2 - 1, 1}, {WIDTH / 2, 1}} // Square
};

void newBrick()
{
    if(++currentIndex == 0) ++currentIndex; // Overflow protection
    for(int i = 0; i < 4; i++) field[movingBrick[i].x + movingBrick[i].y * WIDTH] = currentIndex;
    
    for(int i = 0; i < HEIGHT; i++)
    {
        bool line = true;
        for(int j = 0; j < WIDTH; j++)
        {
            if(field[i * WIDTH + j] == 0)
            {
                line = false;
                break;
            }
        }
        if(line)
        {
            for(int j = i; j > 0; j--)
            {
                // Copy line j-1 to j
                for(int k = 0; k < WIDTH; k++) field[k + j * WIDTH] = field[k + (j-1) * WIDTH];
            }
        }
        
        for(int i = WIDTH * HEIGHT - 1; i >= 0; i--)
        {
            if(field[i] == 0) continue; // No brick that could fall down...
            if(i / WIDTH != HEIGHT - 1 && field[i + WIDTH] == 0) // Below brick is free
            {
                if(i % WIDTH != 0 && field[i - 1] != field[i] && i % WIDTH != WIDTH - 1 && field[i + 1] != field[i] && i / WIDTH != 0 && field[i - WIDTH] != field[i])
                {
                    field[i + WIDTH] = field[i];
                    field[i] = 0;
                }
            }
        }
    }
    
    pos* p = bricks[rand() % 7];
    for(int i = 0; i < 4; i++) {
        movingBrick[i] = p[i];
        if(field[movingBrick[i].x + movingBrick[i].y * WIDTH] != 0)
        {
            currentIndex = 0;
            for(int i = 0; i < WIDTH * HEIGHT; i++) field[i] = 0;
            usleep(1000 * 2000);
            memset(movingBrick, 0, sizeof(pos) * 4);
            pos* p = bricks[rand() % 7];
            for(int i = 0; i < 4; i++) movingBrick[i] = p[i];
            std::cout << "Game over...." << std::endl;
        }
    }
}

void rotateRight()
{
    pos center = movingBrick[1];
    for(int i = 0; i < 4; i++)
    {
        int l = movingBrick[i].x;
        int x = (movingBrick[i].y - center.y) + center.x;
        int y = -(l - center.x) + center.y;
        if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || field[x + y * WIDTH] != 0) return;
    }
    for(int i = 0; i < 4; i++)
    {
        int l = movingBrick[i].x;
        movingBrick[i].x = (movingBrick[i].y - center.y) + center.x;
        movingBrick[i].y = -(l - center.x) + center.y;
    }
}

void rotateLeft()
{
    pos center = movingBrick[1];
    for(int i = 0; i < 4; i++)
    {
        int l = movingBrick[i].x;
        int x = -(movingBrick[i].y - center.y) + center.x;
        int y = (l - center.x) + center.y;
        if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || field[x + y * WIDTH] != 0) return;
    }
    for(int i = 0; i < 4; i++)
    {
        int l = movingBrick[i].x;
        movingBrick[i].x = -(movingBrick[i].y - center.y) + center.x;
        movingBrick[i].y = (l - center.x) + center.y;
    }
}

// Game functions

void Tetris::setupGame()
{
    pos* p = bricks[rand() % 7];
    for(int i = 0; i < 4; i++) movingBrick[i] = p[i];
}

void Tetris::render()
{
    for(int i = 0; i < WIDTH * HEIGHT; i++)
    {
        writePixel(i % WIDTH, i / WIDTH, field[i] == 0 ? 0x000000 : indexToColor(field[i]));
    }
    for(int i = 0; i < 4; i++)
    {
        writePixel(movingBrick[i].x, movingBrick[i].y, indexToColor(currentIndex + 1));
    }
    
    if(++timer >= TIME)
    {
        timer = 0;
        bool couldMove = true;
        for(int i = 0; i < 4; i++)
        {
            if(++movingBrick[i].y >= HEIGHT || field[movingBrick[i].x + movingBrick[i].y * WIDTH] != 0) // Or another brick was hit
            {
                couldMove = false;
            }
        }
        if(!couldMove)
        {
            for(int i = 0; i < 4; i++)
            {
                --movingBrick[i].y;
            }
            newBrick();
        }
    }
}

void Tetris::direction_press(int dir)
{
    if(dir == KEY_RIGHT)
    {
        for(int i = 0; i < 4; i++)
        {
            if(movingBrick[i].x + 1 >= WIDTH || field[movingBrick[i].x + 1 + movingBrick[i].y * WIDTH] != 0) return;
        }
        for(int i = 0; i < 4; i++)
        {
            ++movingBrick[i].x;
        }
    }
    else if(dir == KEY_LEFT)
    {
        for(int i = 0; i < 4; i++)
        {
            if(movingBrick[i].x - 1 < 0 || field[movingBrick[i].x - 1 + movingBrick[i].y * WIDTH]) return;
        }
        for(int i = 0; i < 4; i++)
        {
            --movingBrick[i].x;
        }
    }
    else if(dir == KEY_DOWN) timer = TIME;
}

void Tetris::a_press()
{
    rotateRight();
}

void Tetris::b_press()
{
    rotateLeft();
}
