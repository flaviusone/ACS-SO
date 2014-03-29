/**
  * SO, 2014
  * Lab #6
  *
  * Task #5, lin
  *
  * Changing page acces protection
  */
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "utils.h"

static int pageSize;
static struct sigaction old_action;
char *p;
int how[3] = { PROT_NONE, PROT_READ, PROT_WRITE };


static void segv_handler(int signum, siginfo_t *info, void *context)
{
	char *addr;
	int rc;

	/* Calling the old signal handler by default for TODO 1 */
	/* Comment this line when resolving TODO 2 */
	old_action.sa_sigaction(signum, info, context);

	/* TODO 2 - obtain from siginfo_t the memory location
	which caused the page fault */

	/* TODO 2 - check if the signal is SIGSEGV */

	/* TODO 2 - compute the page number which caused the page fault

		Hint: use the address returned by mmap
         */


	/* TODO 2 - increase protection for each page */


}

static void set_signal() {
	struct sigaction action;
	int rc;

	action.sa_sigaction = segv_handler;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGSEGV);
	action.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &action, &old_action);
	DIE(rc == -1, "sigaction");
}

static void restore_signal() {
	struct sigaction action;
	int rc;

	action.sa_sigaction = old_action.sa_sigaction;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGSEGV);
	action.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &action, NULL);
	DIE(rc == -1, "sigaction");
}

int main() {
	int rc;
	char ch;

	pageSize = getpagesize();

	/* TODO 1 - Map 3 pages with the desired memory protection */
	p = mmap(NULL, 3*pageSize, PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

	mprotect(p + 0*pageSize, pageSize, PROT_NONE);

	mprotect(p + 1*pageSize, pageSize, PROT_READ);

	mprotect(p + 2*pageSize, pageSize, PROT_WRITE);

	set_signal();

	/* TODO 1 - Access these pages for read and write */
	p[0*pageSize] = '1';
	printf("%c\n",p[0*pageSize] );
	p[1*pageSize] = '2';
	printf("%c\n",p[1*pageSize] );
	p[2*pageSize] = '3';
	printf("%c\n",p[2*pageSize] );

	restore_signal();

	return 0;
}
