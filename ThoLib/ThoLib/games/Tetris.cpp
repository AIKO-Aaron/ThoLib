#include "./Game.h"
#include <iostream>
#include <vector>
#include <unistd.h>

#define TIME 60

#undef WIDTH
#undef HEIGHT

#define WIDTH 10
#define HEIGHT 15

unsigned int currentIndex = 0;
bool tet_draw = true;

pos movingBrick[4]; // the moving brick --> all bricks have 4 tiles
unsigned int field[WIDTH * HEIGHT]; // 15 * 10 --> 150 tiles
int gameover = 0;

int indexToColor(int index)
{
    return ((0x123456 * index) % 0xFFFFFF) | 0x101010;
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

bool canFallDown(int i)
{
    if(i % WIDTH != 0 && field[i - 1] == field[i] && (i / WIDTH + 1 <= HEIGHT && field[i - 1 + WIDTH])) return false;
    if(i % WIDTH != WIDTH - 1 && field[i + 1] == field[i] && (i / WIDTH + 1 <= HEIGHT && field[i + 1 + WIDTH])) return false;
    if(i / WIDTH != 0 && field[i - WIDTH] == field[i]) return canFallDown(i - WIDTH);
    
    return true;
}

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
                for(int k = 0; k < WIDTH; k++) {
                    field[k + j * WIDTH] = field[k + (j-1) * WIDTH];
	            }
	        }
        }
        for(int i = WIDTH * HEIGHT - 1; i >= 0; i--)
        {
            if(line) {
                usleep(16000);
                clearPixel(HEIGHT - 2 - (i / WIDTH), i % WIDTH);
            }
            if(field[i] == 0) continue; // No brick that could fall down...
            if(i / WIDTH != HEIGHT - 1 && field[i + WIDTH] == 0) // Below brick is free
            {
                if(canFallDown(i))
                {
                    clearPixel(HEIGHT - 1 - (i / WIDTH), i % WIDTH);
                    field[i + WIDTH] = field[i];
                    field[i] = 0;
                    drawPixel(HEIGHT - (i / WIDTH), i % WIDTH, indexToColor(field[i]));
                    usleep(16000);
                }
            }
            if(line) drawPixel(HEIGHT - 1 - (i / WIDTH), i % WIDTH, indexToColor(field[i]));
        }
    }
    
    pos* p = bricks[rand() % 7];
    for(int i = 0; i < 4; i++) {
        movingBrick[i] = p[i];
        if(field[movingBrick[i].x + movingBrick[i].y * WIDTH] != 0)
        {
            // usleep(1000 * 2000); // sleep 2 seconds
            if(!gameover) gameover = 120;
            std::cout << "Game over...." << std::endl;
            return;
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
	clearPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x);
        int l = movingBrick[i].x;
        movingBrick[i].x = (movingBrick[i].y - center.y) + center.x;
        movingBrick[i].y = -(l - center.x) + center.y;
    }
}

void Tetris::setupGame()
{
    pos* p = bricks[rand() % 7];
    for(int i = 0; i < WIDTH * HEIGHT; i++) field[i] = 0;
    for(int i = 0; i < 4; i++) movingBrick[i] = p[i];
    currentIndex = 1;
}

void Tetris::render()
{
    if(gameover) --gameover;

    if(gameover) {
        if(gameover == 1) {
            for(int i = 0; i < WIDTH * HEIGHT; i++) field[i] = 0;
            pos* p = bricks[rand() % 7];
            for(int i = 0; i < 4; i++) movingBrick[i] = p[i];
        }
    }

    if(++timer >= TIME && !gameover)
    {
        // Clear current brick...
        for(int i = 0; i < 4; i++)
    	{
            drawPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x, 0);
    	}

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
                int inField = movingBrick[i].x + movingBrick[i].y * WIDTH;
                drawPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x, field[inField] == 0?0x000000:indexToColor(field[inField]));
                --movingBrick[i].y;
            }
            for(int i = 0; i < 4; i++)
            {
                drawPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x, indexToColor(currentIndex + 1));
            }
            newBrick();
        }
        tet_draw = true;
    }

    if(tet_draw) {
        for(int i = 0; i < 9; i++) drawPixel(HEIGHT - 1, i, field[i] == 0 ? 0x000000 : indexToColor(field[i])); // Test this....
        for(int i = 0; i < 4; i++)
        {
            drawPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x, indexToColor(currentIndex + 1));
        }
        tet_draw = false;
    }
}

void Tetris::direction_press(int dir)
{
    if(gameover) return;
    tet_draw = true;
    if(dir == KEY_RIGHT)
    {
        for(int i = 0; i < 4; i++)
        {
            clearPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x);
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
            clearPixel(HEIGHT-1-movingBrick[i].y, movingBrick[i].x);
            if(movingBrick[i].x - 1 < 0 || field[movingBrick[i].x - 1 + movingBrick[i].y * WIDTH]) return;
        }
        for(int i = 0; i < 4; i++)
        {
            --movingBrick[i].x;
        }
    } else if(dir == KEY_UP && !gameover) rotateRight();
    else if(dir == KEY_DOWN) timer = TIME;
}

void Tetris::a_press()
{

}

void Tetris::b_press()
{

}
