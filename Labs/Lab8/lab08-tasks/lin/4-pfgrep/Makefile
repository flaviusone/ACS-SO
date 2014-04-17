CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g
LDLIBS = -lpthread

.PHONY: all clean

all: pfgrep

pfgrep: pfgrep.o

pfgrep.o: pfgrep.c ../utils/utils.h

clean:
	-rm -f *.o *~ pfgrep
