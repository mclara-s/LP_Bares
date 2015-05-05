SOURCES=src/bares.cpp src/main.cpp src/sequence.cpp\
		headers/bares.hpp headers/dequeue.hpp headers/queue.hpp headers/sequence.hpp\
		headers/stack.hpp headers/token.hpp\

CFLAGS=-Wall

all:
	$(CC) $(SOURCES) $(CFLAGS) -o bares
	g++ main.cpp -std=c++11 -o bares

clean:
	rm bares