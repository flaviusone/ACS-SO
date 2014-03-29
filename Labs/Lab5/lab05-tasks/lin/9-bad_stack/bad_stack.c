/**
  * SO, 2014
  * Lab #5
  *
  * Task #9, lin
  *
  * Working with the stack
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// char lab_so[6];

static char *myfun(void)
{
	// static char lab_so[6];

	char *lab_so = malloc(6);

	sprintf(lab_so,"%s-%s", "Lab", "4");
	printf("myfun: %s\n", lab_so);

	return &lab_so[0];
}


int main(void)
{
	char *str;

	str = myfun();

	printf("main first: %s\n", str);

	printf("main second: ");
	printf("%s\n", str);

	return 0;
}
