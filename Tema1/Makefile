# Tema 1 SO - Makefile
# Flavius Tirnacop 331CA

CC = gcc
CFLAGS = -Wall -g -DDEBUG
# CFLAGS = -Wall -g
Output = tema1

.PHONY: all clean

all: tema1 run

tema1: tema1.c debug.h utils.h functii.h functii.c

run:
	./tema1

.PHONY: clean
 
clean:
	rm -f *.o *~ $(Output)