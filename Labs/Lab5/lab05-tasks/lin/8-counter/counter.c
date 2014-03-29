/**
  * SO, 2014
  * Lab #5
  *
  * Task #8, lin
  *
  * Process memory zones
  */
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

/**
 * TODO - functia inc() must behave like a counter
 *      The functin returns the next value in order and
 *      does not receive and paramter
 *
 *	You are not allowed to use global variables
 */
int inc()
{
  static int j = 1;
  j++;
  return j;
}


int main(void)
{
	int i;

	for (i = 0; i < 10; i++)
		printf("%d\n", inc());

	return 0;
}

