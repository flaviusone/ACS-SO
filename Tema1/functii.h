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
	unsigned int size;
	Nod **buckets;
} Hashtable;

Hashtable *create_Hashtable(unsigned int size);

int Hash_add(char* word,Hashtable* hashtable);

int Hash_remove(char* word,Hashtable* hashtable);

int Hash_clear(Hashtable* hashtable);

int Hash_find(char* word,char* outfile,Hashtable* hashtable);

int Hash_print_bucket(unsigned int index, char* outfile,Hashtable* hashtable);

int Hash_print(char* outfile,Hashtable* hashtable);

int Hash_resize_double(Hashtable* hashtable);

int Hash_resize_halve(Hashtable* hashtable);

unsigned int hash_function(const char *str, unsigned int hash_length);