CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g
LDLIBS = -lpthread

.PHONY: all clean

all: tsd

tsd: tsd.o

tsd.o: tsd.c ../utils/utils.h

clean:
	-rm -f *.o *~ tsd *.log
