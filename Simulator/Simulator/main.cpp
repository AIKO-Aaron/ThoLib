#include <iostream>


#include "game.h"

int main(int argc, char **args)
{
    srand((int) time(NULL));
    setupGame();
	startLoop();
	// std::cin.get();
	return 0;
}
