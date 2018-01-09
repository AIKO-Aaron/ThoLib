//
//  Input.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 09.01.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

// What controllers are we gonna use?

// --> NES? --> start + stop = reset
// --> Joysticks? (Arcade) (a & b replaced with up/down --> max. 4 buttons instead of 6)
// -->


/**
 Connection ideas:
 
 If gpio:
    Spawn new thread & use python to read from gpio
    (Maybe) Connect controller to arduino & connect 6 wires
 
 Else (Controller -> USB):
    Find library for controller (+usb)
 
 */

#include "Input.h"

userInput getUserInput()
{
    // TODO handle input
    
    
    
    /**
     // Everything is boolean!
     int ud = up - down;
     int lr = left - right;

     if(ud > 0) dir = KEY_UP;
     else if(ud < 0) dir = KEY_DOWN;
     
     // Left right is prioritized .... Maybe needs to be changed if controller is more sensitive on left/right than up/down
     if(lr > 0) dir = KEY_LEFT;
     else if(lr < 0) dir = KEY_RIGHT;
    */
    
    // Default values
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
