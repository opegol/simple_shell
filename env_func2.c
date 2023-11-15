#include "main.h"

char **env_copy(void);
void fre_env(void);
void pr_env(void);
void free_list(list_t *head);

/**
 * env_copy - returns a copy of environ
 * Return: copy of environ
 */
char **env_copy(void)
{
	int i = 0, j;
	char **env;

	while (environ[i])
		i++;

	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (environ[i] != NULL)
	{
		env[i] = str_dup(environ[i]);
		if (!env[i])
		{
			for (j = 0; j <= i; j++)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

/**
 * fre_env - free environ copy
 */
void fre_env(void)
{
	int i = 0;

	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}
#include <stdio.h>
/*#include <unistd.h>*/

/**
 * pr_env - prints the environment
 */
void pr_env(void)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * free_list - frees a list_t list
 * @head : linked list to be freed
 */
void free_list(list_t *head)
{
	list_t *temp;

	while (head)
	{
		temp = head;
		free(temp->str);
		head = head->next;
		free(temp);
	}
}

