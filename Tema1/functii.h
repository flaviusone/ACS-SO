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

typedef struct _Nod{
	char *cuvant;
	struct _Nod *next;
} Nod;

typedef struct _Hashtable{
	uint32_t size;
	Nod **buckets;
} Hashtable;

Hashtable *create_Hashtable(uint32_t size);

int Hash_add(char* word,Hashtable* hash);

int Hash_remove(char* word,Hashtable* hash);

int Hash_clear(Hashtable* hash);

int Hash_find(char* word,char* outfile,Hashtable* hash);

int Hash_print_bucket(uint32_t index, char* outfile,Hashtable* hash);

int Hash_print(char* outfile,Hashtable* hash);

int Hash_resize_double(Hashtable* hash);

int Hash_resize_halve(Hashtable* hash);


