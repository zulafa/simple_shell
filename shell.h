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
} info_t;


#define INFO_INIT \
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
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/*atoi.c */
int interactive(info_t *t);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/*errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/*getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
