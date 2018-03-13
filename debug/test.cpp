#include <iostream>
#include "arduino.h"

arduino teensy;

void writeInt(int x) {
	for(int i = 0; i < 4; i++) writeArduino(teensy, (x >> (24 - 8 * i)) & 0xFF);
}

int main(int argc, char **args) {
	teensy = openArduino();
	for(int i = 0; i < 1200; i++) writeIntArduino(teensy, 0x110011 | (i << 24));
	while(true) std::cout << readArduino(teensy);
}
