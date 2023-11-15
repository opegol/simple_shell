#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

extern char **environ;
/*int exec_hist;*/
/*int newstring_flag;*/
/*char *prog_name;*/

/**
 * struct list_s - defined as a list_t linked list
 * @str : string member of struct
 * @next : struct referring to list_t struct
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct glo_var - contains some global variables
 * @exec_hist : program execution counter
 * @newstring_flag : flag to monitor newstr return value in _which function
 * @prog_name : program name
 */
typedef struct glo_var
{
	int exec_hist;
	int newstring_flag;
	char *prog_name;
} gvar;

int slen(const char *s);
char *_getenv(const char *name);
char **stok(char *str);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_which(char *pathname, gvar *dat);
int builtin_cmd_handler(char **token, char *line, gvar *dat);
int _strcmp(char *s1, char *s2);
char *str_dup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *itostr(int);
int tok_len(char *line, char sep);
void free_all(char **str);
void free_list(list_t *head);
char **env_copy(void);
void fre_env(void);
void pr_env(void);
int print_err_msg(char **token, int err_num, gvar *dat);
int find_env_variable(const char *name);
void replace_env_variable(const char *name, const char *value, char **env);
void add_env_variable(const char *name, const char *value);
ssize_t custom_getline(char **line, size_t *len, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
char **split_string(const char *input_string, const char *delimiter);

/*int execute_command(char *command, char *progname);*/

#endif
