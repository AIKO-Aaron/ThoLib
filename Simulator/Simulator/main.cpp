#include <iostream>
#include <time.h>

#include "game.h"

int main(int argc, char **args)
{
    srand((int) time(NULL));
    //setupInput();
    setupGame();
	startLoop();
	// std::cin.get();
	return 0;
}
