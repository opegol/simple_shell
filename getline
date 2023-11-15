#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

/**
 * getline - Reads a line from standard input.
 *
 * This function reads a line from the standard input using the getline
 * function and dynamically allocates memory to store the input.
 *
 * @lineptr: A pointer to the buffer where the line will be stored.
 * @n: A pointer to the size of the buffer.
 * @stream: A FILE pointer representing the input stream (stdin in this case).
 *
 * Return: The number of characters read, or -1 if an error occurs.
 */

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/**
 * main - function of the simple shell program.
 *
 * This function continuously prompts the user with "$ ", reads their input,
 * and prints the entered command on the next line.
 *
 * Return: 0 on successful execution.
 */

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		/* Print the prompt "$ " */
		printf("$ ");

		/* Read user input until EOF condition (Ctrl+D) is encountered */
		read = getline(&input, &len, stdin);

		/* Check for EOF */
		if (read == -1)
		{
			if (feof(stdin))
			{
				/* User pressed Ctrl+D (EOF), exit gracefully */
				break;
			}
			else
			{
				/* Error while reading input */
				perror("getline");
				break;
			}
		}

		/* Remove newline character from input */
		input[strcspn(input, "\n")] = '\0';

		/* Execute the entered command */
		if (execute_command(input) == -1)
		{
			fprintf(stderr, "Error executing command: %s\n", input);
		}
	}

	/* Free dynamically allocated memory */
	free(input);

	return (0);
}

/**
 * execute_command - Executes a command in a child process.
 *
 * This function takes a command string, parses it into arguments, forks
 * a new process, and executes the command in the child process.
 *
 * @command: The command string to be executed.
 *
 * Return: 0 on successful execution, -1 on failure.
 */

int execute_command(char *command)
{
	pid_t pid, wpid;
	int status;

	/* Fork a new process */
	pid = fork();

	if (pid == 0)
	{
		/* Child process */

		/* Parse the command into arguments */
		char *args[MAX_INPUT_SIZE];
		char *token = strtok(command, " ");
		int i = 0;

		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}

		args[i] = NULL; /* Null-terminate the argument list */

		/* Execute the command */
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* Error forking */
		perror("fork");
		return (-1);
	}
	else
	{
		/* Parent process */

		/* Wait for the child process to complete */
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

		return (0);
	}
}
