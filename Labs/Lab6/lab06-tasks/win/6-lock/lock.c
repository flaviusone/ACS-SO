/**
 * SO, 2014
 * Lab #6, Memoria virtuala
 *
 * Task #6, Windows
 *
 * Locking memory in order to avoid swaping
 */

/* do not use UNICODE */
#undef _UNICODE
#undef UNICODE

#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <windows.h>

#include "utils.h"

#define SIZE	128

static int pageSize = 0x1000;
char msg[] = "Very important real-time data";


int main(void)
{
	char data[SIZE];
	DWORD rc, i;

	/* TODO - Lock data */

	/* TODO - copy msg into data */


	/* printing data to see it's there */
	printf("data=%s %d\n", data);

	/* TODO - UnLock data */

	return 0;
}
