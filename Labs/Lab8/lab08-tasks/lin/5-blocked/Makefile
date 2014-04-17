CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g
LDLIBS = -lpthread

.PHONY: all clean

all: blocked

blocked: blocked.o

blocked.o: blocked.c ../utils/utils.h

clean:
	-rm -f *.o *~ blocked
