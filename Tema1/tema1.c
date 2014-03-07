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

#define BUFFSIZE 20000


void parse_command(char* buffer, Hashtable *hash){

	int res;

	char* token = strtok(buffer, " ");
	char* aux;
	/* Parse add */
	if(strcmp(token,"add") == 0){
		token = strtok(NULL, " ");
		res = Hash_add(token,hash);
		DIE(res<0,"Error in Hash_add");
		return;
	}

	/* Parse remove */
	if(strcmp(token,"remove") == 0){
		token = strtok(NULL, " ");
		res = Hash_remove(token,hash);
		DIE(res<0,"Error in Hash_remove");
		return;
	}

	/* Parse clear */
	if(strcmp(token,"clear\n") == 0){
		res = Hash_clear(hash);
		DIE(res<0,"Error in Hash_clear");
		return;
	}		
	/* Parse find */
	if(strcmp(token,"find") == 0){
		token = strtok(NULL, " ");
		aux = strtok(NULL, " ");
		/* Check if file is an option */
		if(aux != NULL){
			res = Hash_find(token,aux,hash);
			DIE(res<0,"Error in Hash_find");	
		}else{
			res = Hash_find(token,NULL,hash);
			DIE(res<0,"Error in Hash_find");	
		}
		return;
	}
	/* Parse print_bucket */
	if(strcmp(token,"print_bucket") == 0){
		token = strtok(NULL, " ");
		uint32_t index = atoi(token);
		aux = strtok(NULL, " ");
		/* Check if file is an option */
		if(aux != NULL){
			res = Hash_print_bucket(index,aux,hash);
			DIE(res<0,"Error in Hash_print_bucket");	
		}else{
			res = Hash_print_bucket(index,NULL,hash);
			DIE(res<0,"Error in Hash_print_bucket");	
		}
		return;
	}
	/* Parse print */
	if(strcmp(token,"print") == 0){
		aux = strtok(NULL, " ");
		res = Hash_print(aux,hash);
		DIE(res<0,"Error in Hash_print");	
		return;
	}
	if(strcmp(token,"print\n") == 0){
		res = Hash_print(NULL,hash);
		DIE(res<0,"Error in Hash_print");	
		return;
	}
	/* Parse resize */
	if(strcmp(token,"resize") == 0){
		token = strtok(NULL, " ");
		if(strcmp(token,"double\n") == 0){
			res = Hash_resize_double(hash);
			DIE(res<0,"Error in Hash_resize_double");	
		}
		if(strcmp(token,"halve\n") == 0){
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

	int i;
	FILE *f;
	DIE(argc<2,"Invalid Input");

	/* Set hashtable_size */
	uint32_t hashtable_size = atoi(argv[1]);

	/* Allocate Hashtable */
	hash = create_Hashtable(hashtable_size);
	DIE(hash==NULL,"Unable to allocate");

	/* Parse from STDIN */
	if(argc <= 2){

		/* Read Command */
		fgets(buff,BUFFSIZE,stdin);

		while(!feof(stdin)){
			/* Parse Command */
			parse_command(buff,hash);

			/* Read Command */
			fgets(buff,BUFFSIZE,stdin);
		}
	/* Parse from FILES */
	}else{
		for(i = 2 ; i < argc ; i++){
			/* Open file */
			f = fopen(argv[i], "r");
			DIE(f == NULL , "Unable to open File");

			/* Read Command */
			fgets(buff,BUFFSIZE,f);

			while(!feof(f)){
				dprintf("%s\n",buff);
				/* Parse Command */
				parse_command(buff,hash);

				/* Read Command */
				fgets(buff,BUFFSIZE,f);
			}
			/* Close file */
			fclose(f);
		}
	}
	return 0;
}
