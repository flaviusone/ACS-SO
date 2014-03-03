/**
 * SO, 2011
 * Lab #2, Procese
 *
 * Task #2, Linux
 *
 * cat/cp applications
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

#define BUFSIZE		32

int main(int argc, char **argv)
{
	int fd_src, fd_dst, rc, bytesRead;
	char buffer[BUFSIZE];

	if (argc < 2 || argc > 3){
		printf("Usage:\n\t%s source_file [destination_file]\n", argv[0]);
		return 0;
	}

	/* TODO 1 - open source file for reading */
	fd_src = open(argv[1], O_RDONLY);
	DIE(fd_src < 0, "open source_file");


	if (argc == 3) {
		/* TODO 2 - redirect stdout to destination file */

		fd_dst = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0644);
		DIE(fd_dst < 0, "open destination_file");

		rc = dup2(fd_dst, STDOUT_FILENO);
		DIE(rc < 0, "dup2");

		rc = close(fd_dst);
		DIE(rc < 0, "close fd2");

	}

	/* TODO 1 - read from file and print to stdout
		use _only_ read and write functions */
	while (1){
		bytesRead = read(fd_src, buffer, BUFSIZE);
		DIE(bytesRead < 0, "read");
		
		if(bytesRead == 0) break;

		buffer[bytesRead] = '\0';
		
		/* What is wrong here ??*/
		//printf("%s", buffer);
		rc = write(STDOUT_FILENO, buffer, bytesRead);	
		
		DIE(rc < 0, "write");
	}
	

	/* TODO 1 - close file */
	rc = close(fd_src);
	DIE(rc < 0, "close");

	return 0;
}
