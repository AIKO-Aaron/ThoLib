//
//  Input.hpp
//  ThoLib
//
//  Created by Aaron Hodel on 09.01.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Input_h
#define Input_h

#define KEY_RIGHT 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_UP 3

// Combined information of the controller state
typedef struct {
    int direction_press;
    bool a_press, b_press;
} userInput;

userInput getUserInput(); // Retrieve the current controller state

#endif /* Input_h */
