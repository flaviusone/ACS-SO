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

 	if(argc <= 2){
 		while(!feof(stdin)){
			/* Read Command */
 			fgets(buff,BUFFSIZE,stdin);

			/* Parse Command */
 			parse_command(buff,hash);

			/* check if emppy line */
 			if(strcmp(buff,"\n")!=0){
 				dprintf("Parsez\n");
 			}
 		}
 	}else{
 		for(i = 2 ; i < argc ; i++){
			/* Open file */
 			f = fopen(argv[i], "r");
 			DIE(f == NULL , "Unable to open File");


 			while(!feof(f)){

				/* Read Command */
 				fgets(buff,BUFFSIZE,f);

				/* Parse Command */
 				parse_command(buff,hash);

				/* check if emppy line */
 				if(strcmp(buff,"\n")!=0){
 					dprintf("Parsez\n");
 				}
 			}
			/* Close file */
 			fclose(f);
 		}
 	}
 	return 0;
 }