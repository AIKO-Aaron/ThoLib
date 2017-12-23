CC = g++
FLAGS = -O2 --std=c++11 -I${CURDIR} -I${CURDIR}/games -Wwritable-strings
LDFLAGS = -o tholib

all: main.o Snake.o Tetris.o Flappy.o arduino.o tholib.o
	$(CC) $(LDFLAGS) $^

main.o: main.cpp
	$(CC) -c $(FLAGS) $<

arduino.o: Arduino.cpp
	$(CC) -c $(FLAGS) $<

tholib.o: tholib.cpp
	$(CC) -c $(FLAGS) $<

include games/Makefile

clean:
	rm -rf *.o
	rm -rf games/*.o
