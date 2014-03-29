/**
  * SO, 2011
  * Lab #3
  *
  * Task #1, lin
  *
  * Use of "system" library call and of "strace"
  */
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: ./system cmd\n");
		return 0;
	}

	int ret = system(argv[1]);
	DIE(ret < 0, "system");

	return 0;
}
