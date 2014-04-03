/**
 * SO, 2014 - Lab #07, Profiling and Debugging
 * Task #1, Linux
 *
 * Bubble sort
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "bubble-sort.h"

#define MAXLEN		8192

#define ASSEMBLY__	1
#define C__		2
// #define TYPE		ASSEMBLY__
#define TYPE		C__

extern int v[MAXLEN];

#if TYPE == ASSEMBLY__
static __attribute__((noinline)) void swap(int *a, int *b)
{
	__asm__ volatile("movl %0, %%eax;\n"
			"movl %1, %%ebx;\n"
			"movl %%ebx, %0;\n"
			"movl %%eax, %1;\n"
			:
			: "m"(*a), "m"(*b)
			: "%eax", "%ebx");
}
#elif TYPE == C__
static __attribute__((noinline)) void swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}
#endif

static __attribute__((noinline)) void bubble_sort(int *v, size_t len)
{
	int i;
	int swapped = 1;
	while(swapped==1){
		swapped = 0;
		for (i = 0; i < len - 1; i++)
			if (v[i] > v[i+1]){
				swap(&v[i],&v[i+1])	;
				swapped = 1;
			}
	}

}

#ifdef DEBUG
static void init_array_rand(int *v, size_t len)
{
	int i;

	srand(time(NULL));
	for (i = 0; i < len; i++) {
		v[i] = rand();
	}
}


static void print_array(int *v, size_t len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d, ", v[i]);
	printf("\n");
}
#endif

static int is_sorted(int *v, size_t len)
{
	int i;
	for (i = 0; i < len - 1; i++)
		if (v[i] > v[i+1])
				return 0;
	return 1;
}

int main(void)
{
	bubble_sort(v, MAXLEN);

	if (is_sorted(v, MAXLEN))
			printf("Well done... bubble sort finished!\n");
		else
			printf("Ooops... bubble sort failed!\n");
	return 0;
}
