CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g

.PHONY: all clean

all: my_system

system: my_system.o

system.o: my_system.c ../utils/utils.h

clean:
	-rm -f *.o *~ my_system
