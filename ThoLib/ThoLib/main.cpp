//
//  main.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 19.12.17.
//  Copyright © 2017 Aaron Hodel. All rights reserved.
//

#include <iostream>
#include "ThoLib.h"
#include "arduino.h"
#include "games/Game.h" // All games defined in there --> implementation in other classes


int main(int argc, const char * argv[]) {
    setup();
    
    // Instantiate game snake & run
    Game *game = new Snake();
    game->run();
    
    return 0;
}
