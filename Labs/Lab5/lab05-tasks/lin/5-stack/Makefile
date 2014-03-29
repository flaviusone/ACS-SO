CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -g

.PHONY: all clean

all: overflow

overflow: overflow.o

overflow.o: overflow.c ../utils/utils.h

clean:
	-rm -f *.o *~ overflow
