# Tema 1 SO - Makefile
# Flavius Tirnacop 331CA

CC = gcc
CFLAGS = -Wall -g -DDEBUG
# CFLAGS = -Wall -g
Output = tema1

.PHONY: all clean

all: tema1

tema1: tema1.c debug.h utils.h

.PHONY: clean
 
clean:
	rm -f *.o *~ $(Output)