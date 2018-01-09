#include "arduino.h"
#include <string>

static void error(std::string message) {
#ifndef DEBUG_NO_CRASH
	perror(message.c_str());
	exit(EXIT_FAILURE);
#endif
}

arduino openArduino() {
	int fd = open("/dev/ttyACM0", O_RDWR);
	if(fd == -1) error("error: open");
	
	//do some initialisation
	struct termios toptions;
	//get the attributes
	if (tcgetattr(fd, &toptions) == -1) error("error: get attriubutes");
	
	//set baudrate
	speed_t brate = B9600;
	cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

	// 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;
	
	// no flow control
	toptions.c_cflag &= ~CRTSCTS;

	toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	toptions.c_oflag &= ~OPOST; // make raw

	// see: http://unixwiz.net/techtips/termios-vmin-vtime.html
	toptions.c_cc[VMIN]  = 0;
	toptions.c_cc[VTIME] = 0;
	
	//set the attributes
	if(tcsetattr(fd, TCSANOW, &toptions) == -1) error("error: set attriubutes");
	
	return fd;
}

void closeArduino(arduino arduino) {
	close(arduino);
}

unsigned char readArduino(arduino arduino) {
	unsigned char touch;
	if(read(arduino, &touch, sizeof(touch)) == -1) error("error: read");
	return touch;
}

void writeArduino(arduino arduino, unsigned char c) {
	if(write(arduino, &c, sizeof(c)) == -1) error("error: write");
}
