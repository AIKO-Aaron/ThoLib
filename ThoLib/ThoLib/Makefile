CC = g++
FLAGS = -O2

all: main.o arduino.o tholib.o
	$(CC) $^

main.o: main.cpp
	$(CC) -c $(FLAGS) $<

arduino.o: Arduino.c
	$(CC) -c $(FLAGS) $<

tholib.o: tholib.cpp
	$(CC) -c $(FLAGS) $<

clean:
	rm -rf *.o
