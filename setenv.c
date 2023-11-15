#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * find_env_variable - Finds the index of the specified environment variable.
 *
 * @name: Name of the environment variable to find.
 * Return: Index of the environment variable if found, -1 otherwise.
 */

int find_env_variable(const char *name)
{
	for (int i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, strlen(name)) == 0
				&& environ[i][strlen(name)] == '=')
		{
			return (i); /* Environment variable found */
		}
	}
	return (-1); /* Environment variable not found */
}

/**
 * replace_env_variable - Replaces the value of an existing
 * environment variable.
 *
 * @name: Name of the environment variable to replace.
 * @value: New value for the environment variable.
 * @env: Pointer to the environment variable to be replaced.
 */

void replace_env_variable(const char *name, const char *value, char **env)
{
	char *new_env = (char *)malloc(strlen(name) + strlen(value) + 2);

	if (new_env == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	sprintf(new_env, "%s=%s", name, value);
	free(*env);
	*env = new_env;
}

/**
 * add_env_variable - Adds a new environment variable to the environment.
 *
 * @name: Name of the new environment variable.
 * @value: Value of the new environment variable.
 */

void add_env_variable(const char *name, const char *value)
{
	int env_count = 0;

	while (environ[env_count] != NULL)
	{
		env_count++;
	}

	char **new_environ = (char **)malloc(sizeof(char *) * (env_count + 2));

	if (new_environ == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	/* Copy existing environment variables */
	for (int i = 0; i < env_count; i++)
	{
		new_environ[i] = environ[i];
	}

	/* Add the new environment variable */
	new_environ[env_count] = (char *)malloc(strlen(name) + strlen(value) + 2);

	if (new_environ[env_count] == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		free(new_environ);
		exit(EXIT_FAILURE);
	}

	sprintf(new_environ[env_count], "%s=%s", name, value);
	new_environ[env_count + 1] = NULL;

	/* Update the environment pointer */
	environ = new_environ;
}

/**
 * _setenv - Changes or adds an environment variable.
 *
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @overwrite: If 1, overwrite existing value; if 0,
 * do nothing if the variable exists.
 * Return: 0 on success, -1 on failure.
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || value == NULL)
	{
		return (-1); /* Invalid input */
	}

	int index = find_env_variable(name);

	if (index >= 0)
	{
		if (overwrite)
		{
			replace_env_variable(name, value, &environ[index]);
		}
		return (0); /* No change (already exists) */
	}

	add_env_variable(name, value);

	return (0); /* Success */
}

/**
 * main - main function
 *
 * Return: void
 */

int main(void)
{
	/* Add or change an environment variable */
	if (_setenv("MY_VARIABLE", "new_value", 1) == 0)
		printf("Environment variable set or changed successfully.\n");
	else
	{
		printf("Error setting or changing environment variable.\n");
	}

	/* Print the updated environment */
	for (char **env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}

	return (0);
}
