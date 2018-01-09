CC = g++
FLAGS = -O2 --std=c++11 -I${CURDIR} -I${CURDIR}/games
LDFLAGS = -o tholib

all: main.o Snake.o Tetris.o Flappy.o arduino.o Input.o ThoLib.o
	$(CC) $(LDFLAGS) $^

main.o: main.cpp
	$(CC) -c $(FLAGS) $<

arduino.o: arduino.cpp
	$(CC) -c $(FLAGS) $<

Input.o: Input.cpp
	$(CC) -c $(FLAGS) $<

ThoLib.o: ThoLib.cpp
	$(CC) -c $(FLAGS) $<

include games/Makefile

clean:
	rm -rf *.o
	rm -rf games/*.o
	rm tholib
