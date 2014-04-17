/**
  * SO, 2014
  * Lab #8
  *
  * Task #7, lin
  *
  */
#include <pthread.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils.h>

#define BUFFER_SIZE      5
#define NR_ITERATIONS    30

typedef struct {
    int buff[BUFFER_SIZE];
    int count;
} buffer_t;


void init_buffer(buffer_t* b)
{
    memset(b->buff, 0, sizeof(int) * BUFFER_SIZE);
    b->count = 0;
}

void insert_item(buffer_t* b, int item)
{
    b->buff[b->count] = item;
    b->count++;
}

int remove_item(buffer_t* b)
{
    b->count--;
    return b->buff[b->count];
}

int is_buffer_full(buffer_t* b)
{
    return b->count == BUFFER_SIZE;
}

int is_buffer_empty(buffer_t* b)
{
    return b->count == 0;
}

/* the buffer where the producer will place items and from which the consumer will take items */
buffer_t common_area;

pthread_cond_t buffer_not_full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer_fn (void* arg)
{
    int item_to_insert, i, rc;

    for(i = 0; i < NR_ITERATIONS; i++) {
        item_to_insert = rand() % 100;

	/* TODO */

        sleep(rand() % 3);
    }

    return NULL;
}

void* consumer_fn (void* arg)
{
    int item_consumed, i, rc;

    for(i = 0; i < NR_ITERATIONS; i++) {

	/* TODO */

        sleep(rand() % 3);
    }

    return NULL;
}

int main ()
{
    pthread_t producer_th, consumer_th;
	int rc;

    /* initialization */
    init_buffer(&common_area);
    srand(time(NULL));

    /* create the threads */
    rc = pthread_create(&producer_th, NULL, producer_fn, NULL);
	DIE(rc != 0, "pthread_create");
    rc = pthread_create(&consumer_th, NULL, consumer_fn, NULL);
	DIE(rc != 0, "pthread_create");

    /* wait for the threads to finish execution */
    rc = pthread_join(producer_th, NULL);
	DIE(rc != 0, "pthread_join");
    rc = pthread_join(consumer_th, NULL);
	DIE(rc != 0, "pthread_join");

    return 0;
}
