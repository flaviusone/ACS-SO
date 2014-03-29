/**
  * SO, 2011
  * Lab #3
  *
  * Task #3, lin
  *
  * Implementing a minimal shell
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils.h"

#define MAX_LINE_SIZE		256
#define MAX_ARGS		8

#define ERROR			0
#define SIMPLE			1
#define REDIRECT		2
#define PIPE			3
#define SET_VAR			4
#define EXIT			5

static char *verb;
static char **args;
static char *stdin_file;
static char *stdout_file;
static char *stderr_file;

static char *value;
static char *var;

static int type;

static int parse_line(char *line);
static void alloc_mem(void);

/*
 * @filedes  - file descriptor to be redirected
 * @filename - filename used for redirection
 */
static void do_redirect(int filedes, const char *filename)
{
	int rc;
	int fd;

	/* TODO 3 - Redirect filedes into fd representing filename */
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	ret = dup2(fd, filedes);
	DIE(ret < 0, "dup2");

	close(fd);
}

static void set_var(const char *name, const char *value)
{
	/* TODO 2 - Set the environment variable */
	setenv(name, value, 1);
}

static char * expand(const char *name)
{
	/* TODO 2 - Return the value of environment variables */
	return getenv(name);
}

/*
 *  @args - array that contains a simple command with parrameters
 */
static void simple_cmd(char **args)
{
	pid_t pid, wait_ret;
	int status;

	/* TODO 1 - Create a process to execute the command */
	pid = fork();
	switch (pid) {
	case -1:
		/* TODO 1 - error */
		DIE(pid==1,"Fork error");
		break;
	case 0:
		/* redirect standard output if needed */
		if (stdout_file != NULL)
			do_redirect(STDOUT_FILENO, stdout_file);

		/* TODO 1 - child process */

		int ret = execvp(*args,args);
		DIE(ret < 0, "system");
		break;
	default:
		/* TODO 1 -  parent process */
		wait_ret = waitpid(pid,&status,0);
		if (WIFEXITED(status))
			printf("Child %d terminated normally, with code %d\n",
				pid, WEXITSTATUS(status));
		break;
	}


}

int main(void)
{
	char line[MAX_LINE_SIZE];
	alloc_mem();

	while (1) {
		printf("> ");
		fflush(stdout);

		memset(line, MAX_LINE_SIZE, 0);

		if (fgets(line, sizeof(line), stdin) == NULL) {
			exit(EXIT_SUCCESS);
		}

		type = parse_line(line);

		switch (type) {
		case EXIT:
			exit(EXIT_SUCCESS);

		case SET_VAR:
			set_var(var, value);
			break;

		case SIMPLE:
			simple_cmd(args);
			break;
		}
	}

	return 0;
}

static void alloc_mem(void)
{
	args = malloc(MAX_ARGS * sizeof(char*));
}

static int parse_line(char *line)
{
	int ret = SIMPLE;
	char *token;
	
	stdin_file = NULL;
	stdout_file = NULL;
	stderr_file = NULL;

	/* check for exit */
	if (strncmp("exit", line, strlen("exit")) == 0) {
		return EXIT;
	}

	/* var = value */
	if (strchr(line, '=') != 0) {
		char *delim = "=\n";
		token = strtok(line, delim);

		if (token == NULL)
			return ERROR;

		var = strdup(token);

		token = strtok(NULL, delim);
		if (token == NULL)
			return ERROR;
		
		value = strdup(token);
		return SET_VAR;
	}

	/* normal command */
	char *delim = " \t\n";
	token = strtok(line, delim);

	if (token == NULL){
		return ERROR;
	}

	verb = strdup(token);

	/* copy args */
	int idx = 0;
	while (token != NULL){
		if (token[0] == '$'){
			token = expand(token+1);
		}

		if (token == NULL) {
			printf(" Expansion failed\n");
			return ERROR;
		}

		if (strncmp(token, ">", strlen(">")) == 0) {
			if (strlen(token) > strlen(">")) {
				token++;
				stdout_file = strdup(token);
			} else {
				token = strtok(NULL, delim);
				stdout_file = strdup(token);
			}
		} else {
			args[idx++] = strdup(token);
		}

		token = strtok(NULL, delim);
	}

	args[idx++] = NULL;
	return ret;
}
