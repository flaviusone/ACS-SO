/**
  * SO, 2014
  * Lab #8
  *
  * Task #3, lin
  *
  * Thread safety
  */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <utils.h>


int a = 0;


void *thread_function(void *args)
{
	static int b;
	int c = 0;
	int *rez = malloc (sizeof(int));
	*rez = 1;

	sleep(1 + pthread_self() % 4);

	printf("thread %lu found a = %d b = %d c = %d\n",
		(unsigned long)pthread_self(), a, b, c);
	a++;
	b++;
	c++;

	return rez;
}

int main(void)
{

	pthread_t thread1, thread2;
	int rc = 1;
	static int b;
	int c = 0;
	void *rez1, *rez2;

	rc = pthread_create(&thread1, NULL, thread_function, NULL);
	DIE(rc != 0, "pthread_create");


	rc = pthread_create(&thread2, NULL, thread_function, NULL);
	DIE(rc != 0, "pthread_create");


	printf("main found a = %d b = %d c = %d\n", a, b, c);
	a++;
	b++;
	c++;
	sleep(2);
	rc = pthread_join(thread1, &rez1);
	DIE(rc != 0, "pthread_join");

	rc = pthread_join(thread2, &rez2);
	DIE(rc != 0, "pthread_join");
	sleep(2);
	printf("We started %d threads\n", *(int *) rez1 + *(int *)rez2);

	return 0;
}
