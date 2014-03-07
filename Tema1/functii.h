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

Hashtable *create_hashtable(uint32_t size);
