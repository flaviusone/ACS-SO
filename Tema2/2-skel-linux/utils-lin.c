/**
 * Operating Sytems 2013 - Assignment 2
 *
 */

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>

#include "utils.h"
#include "debug.h"

#define READ		0
#define WRITE		1

static char *get_word(word_t *s);

/**
 * Internal change-directory command.
 */
static bool shell_cd(word_t *dir)
{
	int status;
	/* TODO execute cd */
	char *params = get_word(dir);

	if (params != NULL)
        status = chdir(params);
    else{
    	params = getenv("HOME");
    	if(params == NULL){
    		free(params);
    		return EXIT_FAILURE;
    	}else{
    		status = chdir(params);
    		free(params);
    		DIE(status < 0, "Error: shell_cd");
    	}
    }
	return EXIT_SUCCESS;
}

/**
 * Internal exit/quit command.
 */
static int shell_exit()
{
	/* TODO execute exit/quit */

	return SHELL_EXIT;
}

/**
 * Concatenate parts of the word to obtain the command
 */
static char *get_word(word_t *s)
{
	int string_length = 0;
	int substring_length = 0;

	char *string = NULL;
	char *substring = NULL;

	while (s != NULL) {
		substring = strdup(s->string);

		if (substring == NULL) {
			return NULL;
		}

		if (s->expand == true) {
			char *aux = substring;
			substring = getenv(substring);

			/* prevents strlen from failing */
			if (substring == NULL) {
				substring = calloc(1, sizeof(char));
				if (substring == NULL) {
					free(aux);
					return NULL;
				}
			}

			free(aux);
		}

		substring_length = strlen(substring);

		string = realloc(string, string_length + substring_length + 1);
		if (string == NULL) {
			if (substring != NULL)
				free(substring);
			return NULL;
		}

		memset(string + string_length, 0, substring_length + 1);

		strcat(string, substring);
		string_length += substring_length;

		if (s->expand == false) {
			free(substring);
		}

		s = s->next_part;
	}

	return string;
}

/**
 * Concatenate command arguments in a NULL terminated list in order to pass
 * them directly to execv.
 */
static char **get_argv(simple_command_t *command, int *size)
{
	char **argv;
	word_t *param;

	int argc = 0;
	argv = calloc(argc + 1, sizeof(char *));
	assert(argv != NULL);

	argv[argc] = get_word(command->verb);
	assert(argv[argc] != NULL);

	argc++;

	param = command->params;
	while (param != NULL) {
		argv = realloc(argv, (argc + 1) * sizeof(char *));
		assert(argv != NULL);

		argv[argc] = get_word(param);
		assert(argv[argc] != NULL);

		param = param->next_word;
		argc++;
	}

	argv = realloc(argv, (argc + 1) * sizeof(char *));
	assert(argv != NULL);

	argv[argc] = NULL;
	*size = argc;

	return argv;
}

/*
 * @filedes  - file descriptor to be redirected
 * @filename - filename used for redirection
 * from lab 3 SO 2014
 */
static void do_redirect(int filedes, const char *filename,int type)
{
	int rc;
	int fd;

	/* TODO 3 - Redirect filedes into fd representing filename */
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	rc = dup2(fd, filedes);
	DIE(rc < 0, "dup2");

	close(fd);
}

static void free_cmd(char **command){
    // free command
    int i = 0;
    while(command[i] != NULL){
    	free(command[i]);
    	i++;
    }
   	free(command);
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father)
{
	/* Init aux variables */
	int pid,wait_ret,status,size,r;
	/* Init command string list*/
	char **command = get_argv(s,&size);
	char *cmd_verb = get_word(s->verb);

	/* sanity checks */
	DIE(s == NULL,"Parse_simple: NULL command");
	DIE(s->up != father,"Parse_command: Invalid father");

	/* Check exit/quit */
	if((strcmp(cmd_verb,"exit") == 0) || (strcmp(cmd_verb,"quit") == 0)){
		r = shell_exit();
		free_cmd(command);
		free(cmd_verb);
		DIE(r != SHELL_EXIT,"Error: shell_exit");
		return r;

	/* Check CD */
	}else if(strcmp(cmd_verb, "cd") == 0){
		status = shell_cd(s->params);
        free_cmd(command);
        free(cmd_verb);
        return status;
	}

	/* TODO if variable assignment, execute the assignment and return
         * the exit status */

	/* TODO if external command:
         *   1. fork new process
	 *     2c. perform redirections in child
         *     3c. load executable in child
         *   2. wait for child
         *   3. return exit status
	 */
    pid = fork();
	switch (pid) {
    case -1:
        DIE(pid == -1, "Error: fork");
    case 0:

    	if(s->out != NULL){
    		do_redirect(STDOUT_FILENO, get_word(s->out), 0);
    	}

        execvp(command[0], (char *const *) command);
        fprintf(stderr, "Execution failed for '%s'\n", command[0]);
        fflush(stdout);
		free_cmd(command);
        exit(EXIT_FAILURE);
        break;
    default:
        free_cmd(command);
        // asteapta procesul copil sa termine
        wait_ret = waitpid(pid, &status, 0);
        DIE(wait_ret < 0, "Error: waitpid");
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else
            return EXIT_FAILURE;
        break;
    }

	return EXIT_SUCCESS; /* TODO replace with actual exit status */
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool do_in_parallel(command_t *cmd1, command_t *cmd2, int level, command_t *father)
{
	/* TODO execute cmd1 and cmd2 simultaneously */

	return true; /* TODO replace with actual exit status */
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2)
 */
static bool do_on_pipe(command_t *cmd1, command_t *cmd2, int level, command_t *father)
{
	/* TODO redirect the output of cmd1 to the input of cmd2 */

	return true; /* TODO replace with actual exit status */
}

/**
 * Parse and execute a command.
 */
int parse_command(command_t *c, int level, command_t *father)
{
	/* sanity checks */
	int r=1;
	DIE(c == NULL,"Parse_command: NULL command");
	DIE(c->up != father,"Parse_command: Invalid father");

	if (c->op == OP_NONE) {
		/* execute a simple command */
		r = parse_simple(c->scmd, level + 1, c);

		return r;
	}

	switch (c->op) {
	case OP_SEQUENTIAL:
		parse_command(c->cmd1, level + 1, c);
		r = parse_command(c->cmd2, level + 1, c);
		break;

	case OP_PARALLEL:
		/* execute the commands simultaneously */
		r = do_in_parallel(c->cmd1, c->cmd2, level + 1, c);
		break;

	case OP_CONDITIONAL_NZERO:
		/* execute the second command only if the first one returns NON zero */
		r = parse_command(c->cmd1, level + 1, c);
		if(r != 0)
			r = parse_command(c->cmd2, level + 1, c);
		break;

	case OP_CONDITIONAL_ZERO:
		/* execute the second command only if the first one returns zero */
		r = parse_command(c->cmd1, level + 1, c);
		if(r == 0)
			r = parse_command(c->cmd2, level + 1, c);
		break;

	case OP_PIPE:
		/* redirect the output of the first command to the input of the second */
		r = do_on_pipe(c->cmd1, c->cmd2, level + 1, c);
		break;

	default:
		assert(false);
	}

	return r;
}

/**
 * Readline from mini-shell.
 */
char *read_line()
{
	char *instr;
	char *chunk;
	char *ret;

	int instr_length;
	int chunk_length;

	int endline = 0;

	instr = NULL;
	instr_length = 0;

	chunk = calloc(CHUNK_SIZE, sizeof(char));
	if (chunk == NULL) {
		fprintf(stderr, ERR_ALLOCATION);
		return instr;
	}

	while (!endline) {
		ret = fgets(chunk, CHUNK_SIZE, stdin);
		if (ret == NULL) {
			break;
		}

		chunk_length = strlen(chunk);
		if (chunk[chunk_length - 1] == '\n') {
			chunk[chunk_length - 1] = 0;
			endline = 1;
		}

		ret = instr;
		instr = realloc(instr, instr_length + CHUNK_SIZE + 1);
		if (instr == NULL) {
			free(ret);
			return instr;
		}
		memset(instr + instr_length, 0, CHUNK_SIZE);
		strcat(instr, chunk);
		instr_length += chunk_length;
	}

	free(chunk);

	return instr;
}

