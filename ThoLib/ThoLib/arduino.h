#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define DEBUG_NO_CRASH // No spamming because arduino is not connected (Or not being executed on linux)

typedef int arduino;

/*
returns a file descriptor to the device file of the arduino 
and does some initialisation
*/
arduino openArduino(void);

/*
closes the file descriptor of the device file of the arduino
*/
void closeArduino(arduino arduino);

/*
reads a byte from the serial connection (device file) to the arduino
*/
unsigned char readArduino(arduino arduino);

/*
writes a byte in the serial connection (device file) to the arduino
*/
void writeArduino(arduino arduino, unsigned char c);
