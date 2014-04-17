/**
  * SO, 2014
  * Lab #8
  *
  * Task #6, lin
  *
  * Implementing functionality of pthread_once()
  */
#include <pthread.h>
#include "utils.h"

#define ONCE_INITIALIZER { PTHREAD_MUTEX_INITIALIZER, 0 }

struct once_struct {            /* Our equivalent of pthread_once_t */
	pthread_mutex_t mutex;
	int called;
};

struct once_struct once = ONCE_INITIALIZER;

static int one_time_init(struct once_struct *once_control, void (*init)(void))
{
	// int s;

	/*TODO - Ensure that 'init' function is called once, and then call it*/
	pthread_mutex_lock(&(once_control->mutex));

	/* Call the initialization function */
	if (!once_control->called) {
		(*init)();
		once_control->called = 1;
	}


	pthread_mutex_unlock(&(once_control->mutex));
	return 0;
}

/**
 * Remaining code is for testing one_time_init()
 * Do NOT edit this function
 */
static void init_func()
{
	/*
	 * We should see this message only once, no matter how many
	 * times one_time_init() is called
	 */

	printf("Called init_func()\n");
}

static void * threadFunc(void *arg)
{
	/*
	 * The following allows us to verify that even if a single thread calls
	 * one_time_init() multiple times, init_func() is only called once
	 */
	printf("Thread %p executing \n", arg);


	one_time_init(&once, init_func);
	one_time_init(&once, init_func);

	return NULL;
}

int main(void)
{
	pthread_t t1, t2;
	int s;

	/* Create two threads, both of which will call one_time_init() */

	s = pthread_create(&t1, NULL, threadFunc, (void *) 1);
	DIE(s != 0, "pthread_create");

	s = pthread_create(&t2, NULL, threadFunc, (void *) 2);
	DIE(s != 0, "pthread_create");

	s = pthread_join(t1, NULL);
	DIE(s != 0, "pthread_join");

	printf("First thread returned\n");

	s = pthread_join(t2, NULL);
	DIE(s != 0, "pthread_join");

	printf("Second thread returned\n");

	exit(EXIT_SUCCESS);
}

