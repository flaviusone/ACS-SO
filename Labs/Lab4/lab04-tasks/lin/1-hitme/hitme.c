/**
  * SO, 2014
  * Lab #4
  *
  * Task #1, lin
  *
  * Catching signals
  */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "utils.h"

int must_leave = 0;

static void sig_handler(int signum)
{
	switch(signum) {
	case SIGTSTP:
		printf("H");
		break;
	case SIGTTIN:
		printf("e");
		break;
	case SIGTTOU:
		printf("l");
		break;
	case SIGURG:
		printf("l");
		break;
	case SIGXCPU:
		printf("o");
		break;
	case SIGXFSZ:
		printf("\n");
		must_leave = 1;
		break;
	default:
		printf("Go back and send the following signals: 20, 21, 22, 23, 24");
		must_leave = 1;
	}
	fflush(stdout);
}

int main(void)
{
	struct sigaction signals;
	sigset_t mask;
	int rc;

	sigemptyset(&mask);

	memset(&signals, 0, sizeof(struct sigaction));
	signals.sa_flags = 0;
	signals.sa_mask = mask;

	signals.sa_handler = sig_handler;

	rc = sigaction(SIGTSTP, &signals, NULL);
	DIE(rc == -1, "sigaction");

	rc = sigaction(SIGTTIN, &signals, NULL);
	DIE(rc == -1, "sigaction");

	rc = sigaction(SIGTTOU, &signals, NULL);
	DIE(rc == -1, "sigaction");

	rc = sigaction(SIGURG,  &signals, NULL);
	DIE(rc == -1, "sigaction");

	rc = sigaction(SIGXCPU, &signals, NULL);
	DIE(rc == -1, "sigaction");

	rc = sigaction(SIGXFSZ, &signals, NULL);
	DIE(rc == -1, "sigaction");

	while(!must_leave) sleep(1);

	return 0;
}
