CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g
LDLIBS = -lpthread

.PHONY: all clean

all: vars malloc

vars: vars.o

vars.o: vars.c ../utils/utils.h

malloc: malloc.o

malloc.o: malloc.c ../utils/utils.h

clean:
	-rm -f *.o *~ vars malloc
