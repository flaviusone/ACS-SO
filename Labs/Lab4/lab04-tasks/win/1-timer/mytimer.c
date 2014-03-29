/**
 * SO, 2014 - Lab #4, Semnale
 * Task #3, Windows
 *
 * Timers usage.
 */

#define _WIN32_WINNT	0x0500

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <windows.h>

#include "util.h"

#define _SECOND		10000000
#define TIMEOUT		(-2 * _SECOND)


/*
 * rutina APC asociata timer-ului
 */

static VOID CALLBACK TimerAPCProc(LPVOID lpArgToCompletionRoutine,
		DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	/* TODO */
}

/*
 * initializeaza si configureaza timer
 */

static void InitSetTimer(void)
{
	/* TODO */
}

int main(void)
{
	InitSetTimer();		/* configureaza timer la 2 secunde */

	while (1) {
		/* asteapta timer */
		/* TODO */
	}

	return 0;
}
