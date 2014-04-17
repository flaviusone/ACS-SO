CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g
LDLIBS = -lpthread

.PHONY: all clean

all: ft

ft: ft.o

ft.o: ft.c ../utils/utils.h

clean:
	-rm -f *.o *~ ft
