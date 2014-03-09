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
#include <string.h>
#include "debug.h"
#include "utils.h"
#include "functii.h"

#define BUFFSIZE 20000


void parse_command(char* buffer, Hashtable *hash){
	char* token;
	char* aux;
	int res;
	unsigned int index;

	if(strcmp(buffer,"\n") == 0) return;

	token = strtok(buffer, " \n");

	/* Parse add */
	if(strcmp(token,"add") == 0){
		token = strtok(NULL, " \n");
		res = Hash_add(token,hash);
		DIE(res<0,"Error in Hash_add");
		return;
	}

	/* Parse remove */
	if(strcmp(token,"remove") == 0){
		token = strtok(NULL, " \n");
		res = Hash_remove(token,hash);
		DIE(res<0,"Error in Hash_remove");
		return;
	}

	/* Parse clear */
	if(strcmp(token,"clear") == 0){
		res = Hash_clear(hash);
		DIE(res<0,"Error in Hash_clear");
		return;
	}
	/* Parse find */
	if(strcmp(token,"find") == 0){
		/* Get Word and File */
		token = strtok(NULL, " \n");
		aux = strtok(NULL, " \n");

		res = Hash_find(token,aux,hash);
		DIE(res<0,"Error in Hash_find");
		return;
	}
	/* Parse print_bucket */
	if(strcmp(token,"print_bucket") == 0){
		/* Get Index and File */
		token = strtok(NULL, " \n");
		DIE(token == NULL, "Null token");
		index = atoi(token);
		aux = strtok(NULL, " \n");

		res = Hash_print_bucket(index,aux,hash);
		DIE(res<0,"Error in Hash_print_bucket");
		return;
	}
	/* Parse print */
	if(strcmp(token,"print") == 0){
		/* Get File */
		aux = strtok(NULL, " \n");

		res = Hash_print(aux,hash);
		DIE(res<0,"Error in Hash_print");
		return;
	}

	/* Parse resize */
	if(strcmp(token,"resize") == 0){
		token = strtok(NULL, " \n");
		if(strcmp(token,"double") == 0){
			res = Hash_resize_double(hash);
			DIE(res<0,"Error in Hash_resize_double");
		}
		if(strcmp(token,"halve") == 0){
			res = Hash_resize_halve(hash);
			DIE(res<0,"Error in Hash_resize_halve");
		}
		return;
	}
	return;
}

Hashtable* hash;
char buff[BUFFSIZE];

int main(int argc,char* argv[]){

	int i,res;
	FILE *f;
	unsigned int hashtable_size;
	DIE(argc<2,"Invalid Input");

	/* Set hashtable_size */
	hashtable_size = atoi(argv[1]);

	/* Allocate Hashtable */
	hash = create_Hashtable(hashtable_size);
	DIE(hash==NULL,"Unable to allocate");

	/* Parse from STDIN */
	if(argc <= 2){

		while(fgets(buff,BUFFSIZE,stdin) != NULL){
			/* Parse Command */
			parse_command(buff,hash);
		}
	/* Parse from FILES */
	}else{
		for(i = 2 ; i < argc ; i++){
			/* Open file */
			f = fopen(argv[i], "r");
			DIE(f == NULL , "Unable to open File");

			/* Read Command */
			while(fgets(buff,BUFFSIZE,f) != NULL){
				dprintf("%s\n",buff);
				/* Parse Command */
				parse_command(buff,hash);
			}
			/* Close file */
			fclose(f);
		}
	}

	/* Free all memory */
	res = Hash_clear(hash);
	DIE(res < 0, "Error in hash_clear");
	free(hash->buckets);
	free(hash);

	return 0;
}
