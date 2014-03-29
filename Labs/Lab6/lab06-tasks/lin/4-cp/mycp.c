/**
  * SO, 2014
  * Lab #6
  *
  * Task #4, lin
  *
  * Implementing 'cp' with mmap
  */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

int main (int argc, char *argv[])
{
	int fdin, fdout, rc;
	char *src, *dst;
	struct stat statbuf;

	DIE(argc != 3, "Usage: ./mycp <from_file> <to_file>");

	/* Open input and output files */
	fdin = open (argv[1], O_RDONLY);
	DIE(fdin == -1, "open fdin");

	/* Open/create the output file */
	fdout = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	DIE(fdout == -1, "open fdout");

	/* TODO - truncate the output file to the input file size */
	fstat (fdin, &statbuf);
	ftruncate(fdout, statbuf.st_size);

	/* TODO - mmap the input and output file */
	src = mmap (0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
	dst = mmap (0, statbuf.st_size, PROT_WRITE,MAP_SHARED, fdout, 0);

	/* TODO - copy the input file to the output file */
	memcpy (dst, src, statbuf.st_size);

	/* TODO - clean up */
	munmap(src, statbuf.st_size);
	munmap(src, statbuf.st_size);


	/* Close files */
	rc = close(fdin);
	DIE(rc == -1, "close source");

	rc = close(fdout);
	DIE(rc == -1, "close destination");

	return 0;
}
