CC = g++
SRCS = src/main.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
INCLUDES = -Iheaders
CFLAGS = -Wall -g -std=c++11 

all: $(OBJS) bares
 
$(OBJS): $(SRCS)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
 
bares:
	$(CC) $(CFLAGS) $(OBJS) -o bares