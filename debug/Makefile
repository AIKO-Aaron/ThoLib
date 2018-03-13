CC = g++
FLAGS = -O2 --std=c++11 -I${CURDIR}
LDFLAGS = -o test

all: test.o arduino.o
	$(CC) $(LDFLAGS) $^

test.o: test.cpp
	$(CC) -c $(FLAGS) $<

arduino.o: arduino.cpp
	$(CC) -c $(FLAGS) $<

clean:
	rm -rf *.o
