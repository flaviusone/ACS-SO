/**
 * Tema 1 SO - Hashtable
 *
 * Copyright (C) 2014, Flavius Tirnacop 331CA <flavius.tirnacop@cti.pub.ro>
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "debug.h"
#include "utils.h"
#include "functii.h"


/**
 * Allocate memory for hashtable
 */
Hashtable *create_Hashtable(unsigned int size){
	Hashtable *hash;

	DIE(size<1,"Invalid size");

	/* Allocate memory for whole hashtable */
	hash = malloc(sizeof(Hashtable));
	if(hash == NULL)  return NULL;

	/* Allocate memory for the buckets */
	hash->buckets = calloc(size,sizeof(Nod*));
	if(hash->buckets == NULL)  return NULL;

	hash->size = size;

	return hash;
}

int Hash_add(char* word,Hashtable* hash){
	printf("I am in function Hash_add\n");
	return 1;
}

int Hash_remove(char* word,Hashtable* hash){
	printf("I am in function Hash_remove\n");
	return 1;
}

int Hash_clear(Hashtable* hash){
	printf("I am in function Hash_clear\n");
	return 1;
}

/**
 * Searches for a word in the hashtable
 * If file is provided prints True/False
 * If file is not provided prints True/False at console (stdout)
 */
int Hash_find(char* word,char* outfile,Hashtable* hash){
	FILE* g;
	/* Compute Index */
	unsigned int index = hash_function(word,hash->size);
	int found = 0;
	Nod* nod = hash->buckets[index];

	/* Search trough Node list at entry index */
	while(nod!=NULL){
		if(strcmp(nod->cuvant,word) == 0){
			found = 1;
		}
		nod = nod->next;
	}

	if(outfile == NULL)
		if(found) 
			printf("True\n");
		else
			printf("False\n");
	else{

		/* Open file in append mode */
		g = fopen(outfile,"a");
		DIE(g<0,"Error in Opening file (Hash_find)");

		if(found) 
			fprintf(g,"True\n");
		else
			fprintf(g,"False\n");
	}
	return 1;
}

int Hash_print_bucket(unsigned int index, char* outfile,Hashtable* hash){
	
	if(outfile == NULL)
		printf("I am in function Hash_print_bucket cu index %d\n",index);
	else
		printf("I am in function Hash_print_bucket cu fisier cu index %d\n",index);
	return 1;
}

int Hash_print(char* outfile,Hashtable* hash){
	printf("I am in function Hash_print\n");
	return 1;
}

int Hash_resize_double(Hashtable* hash){
	printf("I am in function Hash_resize_double\n");
	return 1;
}

int Hash_resize_halve(Hashtable* hash){
	printf("I am in function Hash_resize_halve\n");
	return 1;
}

/**
 * Functie de hash bazata pe djb2 a lui Dan Bernstein
 * http://www.cse.yorku.ca/~oz/hash.html
 * @return valoarea de dispersie (cheia)
 */
unsigned int hash_function(const char *str, unsigned int hash_length)
{
	unsigned int hash = 5381;
	int c;

	while ( (c = *str++) != 0 )
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash % hash_length);
}

