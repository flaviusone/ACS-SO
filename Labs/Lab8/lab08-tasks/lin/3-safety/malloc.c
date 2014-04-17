/**
  * SO, 2014
  * Lab #8
  *
  * Task #3, lin
  *
  * Is malloc thread safe?
  */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <utils.h>

#define N 1000
#define M 100

void *th_alloc(void * args)
{
	int i;

	char **a;
	a = malloc (M  * sizeof(char*));
	for (i = 0; i < M; i++)
		a[i] = malloc(M);

	return a;
}

void free_mat(void **mat)
{
	int i;
	char **m = (char**) mat;
	for (i = 0; i < M; i++)
		free(m[i]);
	free(m);
}

int main(void)
{

	pthread_t th[N];
	int i, rc;
	void *mat[N];

	for (i = 0; i < N; i++){
		rc = pthread_create(&th[i], NULL, th_alloc, &i);
		DIE(rc != 0, "create");
	}

	for (i = 0; i < N; i++){
		rc = pthread_join(th[i], &mat[i]);
		DIE(rc != 0, "join");
	}

	/* Freeing */
	for (i = 0; i < N; i++){
		free_mat(mat[i]);
	}


	return 0;
}
