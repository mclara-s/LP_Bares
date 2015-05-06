SOURCES=src/main.cpp\

CFLAGS=-Wall

all:
	$(CC) $(SOURCES) $(CFLAGS) -o bares

clean:
	rm bares
