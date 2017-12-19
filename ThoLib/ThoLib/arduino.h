/*
returns a file descriptor to the device file of the arduino 
and does some initialisation
*/
int openArduino(void);

/*
closes the file descriptor of the device file of the arduino
*/
void closeArduino(int arduino);

/*
reads a byte from the serial connection (device file) to the arduino
*/
unsigned char readArduino(int arduino);

/*
writes a byte in the serial connection (device file) to the arduino
*/
void writeArduino(int arduino, unsigned char c);
