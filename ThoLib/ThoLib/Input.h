//
//  Input.hpp
//  ThoLib
//
//  Created by Aaron Hodel on 09.01.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Input_h
#define Input_h

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>

#include <pthread.h>

#define KEY_RIGHT 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_UP 3

#define BUF_SIZE 8 // Don't change...

typedef struct {
    uint32_t time;
    uint16_t value;
    uint8_t type;
    uint8_t number;
} input_event;

// Combined information of the controller state
typedef struct
{
    int direction_press;
    bool a_press, b_press;
    bool start_press, select_press;
} userInput;

void setupInput();
void closeInput();
userInput getUserInput(); // Retrieve the current controller state

#endif /* Input_h */
