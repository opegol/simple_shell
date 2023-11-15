#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _unsetenv - Deletes the specified variable from the environment.
 *
 * This function removes the specified environment variable from the
 * environment array.
 *
 * @name: The name of the environment variable to be removed.
 *
 * Return: 0 on success, -1 if the variable is not found or on failure.
 */

int _unsetenv(const char *name)
{
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
	{
		fprintf(stderr, "Invalid variable name.\n");
		return (-1);  /* Invalid input */
	}

	char **env = environ;

	while (*env != NULL)
	{
		if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=')
		{
			/* Environment variable found, remove it */
			free(*env);  /* Free the memory occupied by the variable string */

			/* Shift the remaining environment variables */
			while (*env != NULL)
			{
				*env = *(env + 1);
				env++;
			}
			return (0);  /* Success */
		}
		env++;
	}

	fprintf(stderr, "Variable not found: %s\n", name);
	return (-1);  /* Environment variable not found */
}

/**
 * main - main function
 *
 * Return: 0 on success, non-zero on failure
 */

int main(void)
{
	/* Delete an environment variable */
	if (_unsetenv("MY_VARIABLE") == 0)
	{
		printf("Environment variable removed successfully.\n");
	}
	else
	{
		fprintf(stderr, "Error removing environment variable.\n");
		return (1);  /* Return non-zero on failure */
	}

	/* Print the updated environment */
	for (char **env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}

	return (0);  /* Success */
}

