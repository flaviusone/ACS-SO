# Tema 1 SO - Makefile
# Flavius Tirnacop 331CA

# CFLAGS = -Wall -g -DDEBUG
CFLAGS = -Wall -g
Output = tema1

.PHONY: all clean

all: tema1 run

build: tema1

run:
	./tema1 10

tema1: tema1.c debug.h utils.h functii.h functii.c 

.PHONY: clean
 
clean:
	rm -f *.o *~ $(Output)