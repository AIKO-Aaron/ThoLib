//
//  Input.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 09.01.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Input.h"

userInput getUserInput()
{
    // TODO handle input
    
    /**
     // Everything boolean
     int ud = up - down;
     int lr = left - right;

     if(ud > 0) dir = KEY_UP;
     else if(ud < 0) dir = KEY_DOWN;
     if(lr > 0) dir = KEY_LEFT;
     else if(lr < 0) dir = KEY_RIGHT;
    */
    
    int direction = KEY_UP;
    bool a_press = false;
    bool b_press = false;
    
    return
    {
        direction,
        a_press,
        b_press
    };
    
}
