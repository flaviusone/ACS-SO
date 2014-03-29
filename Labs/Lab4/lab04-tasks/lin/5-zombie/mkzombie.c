/**
  * SO, 2014
  * Lab #4
  *
  * Task #5, lin
  *
  * Creating zombies
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"

#define TIMEOUT		20


int main(void)
{
	pid_t pid;
  int status;

  pid = fork();
  switch (pid) {
    case -1:
      DIE(pid, "fork");
      break;

    case 0:
      exit(EXIT_SUCCESS);
      break;

    default:
      break;
  }



  sleep(TIMEOUT);

  return 0;
}
