//
//  main.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 19.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

#include <iostream>
#include "Input.h"
#include "ThoLib.h"
#include "arduino.h"
#include "games/Game.h" // All games defined in there --> implementation in other classes


int main(int argc, const char * argv[]) {
    setup();
    setupInput();

    // Instantiate game snake & run it
    Game *game = new Snake(); //new Flappy();
    game->run();
    
    return 0;
}
