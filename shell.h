#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * *struct liststr - rep the singly linked list
 * @num: rep the number of the field
 * @str: rep the string
 * @next: rep the points to the next mode
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}
list_t;
/**
 * struct pass info - this is a function that contains
 * pseudo-arguments.
 * @program_name: name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to first command typed by user
 * @tokens: pointer to array of tokenized input
 * @exec_counter: number of executed commands
 * @arg: rep a string that has been essentially generated
 * which contains arguments.
 * @argv: rep an array of strings generated
 * from arg
 * @path: rep a string path for the current command
 * @argc : rep the argument count
 * @line_count: rep the error count encountered during
 * the line count.
 * @err_num: rep the error code for exit()s
 * @linecount_flag: tends to consider if the cout
 * is on this line of input.
 * @fname: rep the filename.
 * @env: rep the environment.
 * @environ: rep the copy of the LL from env.
 * @history: rep the history node.
 * @alias: rep the alias node.
 * @env_changed: checks if the env has been modified.
 * @status: a function that will return the status of the last executed
 * command.
 * @cmd_buf: rep CMD_type ||, &&, ;
 * readfd: rep the fd from where the line input is read
 * @histcount: rep the number count of the history line.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	int err_num;
	char *fname;
	unsigned int line_count;
	int linecount_flag;
	list_t *env;
	list_t *history;
	list_t *alias;
	char *environ;
	int env_changed;
	int status;
	int readfd;
	int histcount;
	int cmd_buf_type;
	char **cmd_buf;
	char *program_name;
	char *input_line;
	char **tokens;
	char *command_name;
	char **env;;
} info_t;
program_data;

#define INFO_INIT
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, \
	NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - this is a function that contains a builtin
 * string and related function.
 * @type: rep the builtin command flag.
 * @func: rep the function
 */
typedef struct builtin
{
	char *builtin;
	int (*function)(program_data *data);
} builtins;

/*toem_shloop.c */
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*======== expand.c ========*/


/* expand variables */
void expand_variables(program_data *data);

/* expand aliases */
void expand_alias(program_data *data);

/* append string at buffer end */
int buffer_add(char *str_to_add, char *buffer);


/*======== str_tok.c ========*/


/* separates strings with delimiters */
char *_strtok(char *delim, char *line);

/* detaches the string by applying a designed delimiter */
void tokenize(program_data *data);


/*======== execute.c ========*/


/* execute command with its entire path variables */
int execute(program_data *data);


/*======== builtins_list.c ========*/


/* finds match and execute the associate builtin */
int builtins_list(program_data *data);


/*======== find_path.c ========*/


/* find program in path */
int find_program(program_data *data);

/* tokenize path in directories */
char **tokenize_path(program_data *data);


/*======== builtins_more.c ========*/


/* program exit with status */
int builtin_exit(program_data *data);

/* change current directory */
int builtin_cd(program_data *data);

/* set work directory */
int set_work_directory(program_data *data);

/* add, remove or display aliases */
int builtin_alias(program_data *data);

/* displays environment where shell runs */
int builtin_help(program_data *data);


/*======== builtins_env.c ========*/


/* displays the environment where the shell runs */
int builtins_env(program_data *data);

/* override or create variable of environment */
int builtin_set_env(program_data *data);

/* delete a variable of environment */
int builtin_unset_env(program_data *data);

<<<<<<< HEAD
=======

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *strcat(char *, char *);

>>>>>>> 3ddb0f2d59112d11f5b119ee1cde828d57d32593
/* toem_string1.c */
char *strcpy(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/*toem_atoi.c */
int interactive(info_t *t);
int _isalpha(int);
int _atoi(char *);

/*======== _getline.c ========*/

int _getline(program_data *data);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *int);

/* toem_environ.c */
char **getenv(info_t *, const char *);
int populate_env_list(info_t *);

/*toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
#endif
