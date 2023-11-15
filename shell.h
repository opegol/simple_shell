#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

/* Function prototypes */
int find_env_variable(const char *name);
void replace_env_variable(const char *name, const char *value, char **env);
void add_env_variable(const char *name, const char *value);
int _setenv(const char *name, const char *value, int overwrite);
ssize_t custom_getline(char **line, size_t *len, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int execute_command(char *command);
int _unsetenv(const char *name);
char **split_string(const char *input_string, const char *delimiter);
/*char **split_string(const char *input_string, const char *delimiter, int *word_count);*/
void print_words(char **words, int word_count);
void free_words(char **words, int word_count);

#endif /* SHELL_H */
