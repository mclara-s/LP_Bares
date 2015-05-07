CC = g++
SRCS = $(wildcard src/*.cpp headers/*.hpp\)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
INCLUDES = -Iheaders
CFLAGS = -Wall -g -std=c++11 
 
all: $(OBJS) bares
 
$(OBJS): $(SRCS) %.o %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
 
bares:
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o bares
 
clean:
	rm -f $(OBJS) bares