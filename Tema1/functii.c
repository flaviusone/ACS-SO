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
#include "debug.h"
#include "utils.h"
#include "functii.h"


/**
 * Allocate memory for hashtable
 */
Hashtable *create_Hashtable(uint32_t size){
	Hashtable *hash;

	DIE(size<1,"Invalid size");

	/* Allocate memory for whole hashtable */
	hash = malloc(sizeof(Hashtable));
	if(hash == NULL)  return NULL;

	/* Allocate memory for the buckets */
	hash->buckets = calloc(size,sizeof(Nod*));
	if(hash->buckets == NULL)  return NULL;

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

int Hash_find(char* word,char* outfile,Hashtable* hash){
	printf("I am in function Hash_find\n");
	return 1;
}

int Hash_print_bucket(uint32_t index, char* outfile,Hashtable* hash){
	printf("I am in function Hash_print_bucket\n");
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