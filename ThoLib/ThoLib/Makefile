CC = g++
FLAGS = -O2

all: main.o
	$(CC) $^

main.o: main.cpp
	$(CC) -c $(FLAGS) $<

clean:
	rm -rf *.o
