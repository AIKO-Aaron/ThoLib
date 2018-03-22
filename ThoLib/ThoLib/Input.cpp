//
//  Input.cpp
//  ThoLib
//
//  Created by Aaron Hodel on 09.01.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//*/

#include "Input.h"

static int direction;
bool b_a = false, b_b = false;
bool b_start = false, b_select = false;
bool right, left, up, down;
pthread_t thread;

void *input_loop(void* args) {
    int fd = open("/dev/input/js0", O_RDONLY);
    char r[BUF_SIZE];
    if(fd == -1) {
        printf("Error opening file...");
        exit(1);
    }
    int i = 0;
    while(1) {
        int n = read(fd, (void*) r, sizeof(char) * BUF_SIZE);
        if(n <= 0) continue;
        else if(n == 8) {
            input_event e = (*(input_event*)r);
            // printf("Timestamp: %d, Value: %d, Number: %d, Type: %d\n", e.time, e.value, e.number, e.type);
            if(e.type == 1) {
                //printf("Button: %d, pressed: %d\n", e.number, e.value);
                if(e.number == 1) b_a = e.value == 1;
                if(e.number == 0) b_b = e.value == 1;
                if(e.number == 8) b_start = e.value == 1;
                if(e.number == 9) b_select = e.value == 1;
            } else if(e.type == 2) {
                int axis = e.value & 0x3;
                //printf("D-Pad: %d, value: %d\n", e.number, axis);
                
                if(e.number == 0) right = axis == 3;
                if(e.number == 0) left = axis == 1;
                if(e.number == 1) down = axis == 3;
                if(e.number == 1) up = axis == 1;
                
                if(right) direction = KEY_RIGHT;
                else if(left) direction = KEY_LEFT;
                else if(up) direction = KEY_UP;
                else if(down) direction = KEY_DOWN;
            	else direction = -1;
	    }
        }
    }
}

void setupInput() {
    void *args = malloc(8);
    pthread_create(&thread, NULL, input_loop, args);
}

void closeInput() {
    pthread_cancel(thread);
}

userInput getUserInput()
{
    // TODO handle input
    // Default values
    
    return
    {
        direction,
        b_a,
        b_b,
    	b_select,
	b_start
    };
    
}
