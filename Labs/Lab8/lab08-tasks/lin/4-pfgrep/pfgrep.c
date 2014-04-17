/**
  * SO, 2014
  * Lab #8
  *
  * Task #4, lin
  *
  * Parallel implementation of  'fgrep -c'
  */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "utils.h"

#define MIN(a,b)	((a) < (b) ? (a) : (b))
#define NUM_THREADS 4

struct params {
	char *mem;
	int len;
};
struct params th_params[NUM_THREADS];
char *string;


void* thread_code(void *args)
{
	struct params *p;
	int i;
	int *number = calloc(1,sizeof(int));
	int string_length = strlen(string);

	/* TODO - get parameters from args */
	p = (struct params*) args;

	/* TODO - Search for string */
	for(i = 0; i < p->len - string_length ; i++)
	{
		if (memcmp(p->mem + i, string, string_length) == 0){
			*number += 1;
		}
	}


	/* TODO - Return how many times string appeared in this chunk */

	return number;
}

static void set_file(char *filename)
{
	int fd, rc, chunk_size, ofs, i, len;
	struct stat statbuf;
	char *mem;

	fd = open(filename, O_RDONLY);
	DIE(fd == -1, "open");

	rc = fstat (fd, &statbuf);
	DIE(rc == -1, "fstat");

	len = statbuf.st_size;

	mem = mmap(0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	DIE(mem == MAP_FAILED, "mmap");

	/* Split mem into chunk for each thread
	   Initialize th_params structures for each thread */
	chunk_size = (len + NUM_THREADS - 1) / NUM_THREADS;
	ofs = 0;

	for (i = 0; i < NUM_THREADS; ofs += th_params[i].len, i++) {
		th_params[i].len = MIN(chunk_size, len - i * chunk_size);
		th_params[i].mem = mem + ofs;
	}

}
int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("Usage: %s string file\n", argv[0]);
		exit(1);
	}

	pthread_t th_id[NUM_THREADS];
	int i, rc;
	void *rez[NUM_THREADS];
	string = argv[1];

	set_file(argv[2]);

	/* TODO - Start threads
	*		- thread i will run 'thread_code' function
	*		passing th_params[i] as parameter
	*/
	for (i = 0; i < NUM_THREADS; i++){
		rc = pthread_create(&th_id[i], NULL, thread_code, &th_params[i]);
		DIE(rc != 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++){
		rc = pthread_join(th_id[i], &rez[i]);
		DIE(rc != 0, "pthread_join");
	}

	/* TODO - Wait for threads to finish and collect results */

	int total = 0;

	/* TODO - Compute final sum */
	for (i = 0; i < NUM_THREADS; i++){
		total +=  *(int *)rez[i];
		// printf("%d",rez[i])
	}


	printf("total = %d\n", total);

	return 0;
}
