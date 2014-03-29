/**
  * SO, 2014
  * Lab #5
  *
  * Task #3, lin
  *
  * Use of gdb to solve "Segmentation fault" problems
  */
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *buf;

	buf = malloc(1<<30);

	printf("Give input string:");
	fgets(buf, 1024, stdin);
	printf("\n\nString is %s\n", buf);

	return 0;
}
