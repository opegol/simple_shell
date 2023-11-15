#include "main.h"

int sslen(char *s);
char *_mstrcat(char *str1, char *str2);
char *_which(char *pathname, gvar *dat);
int path_depth(char *s);
list_t *path_list(void);

/**
 * sslen - get string length
 * @s : given string
 * Return: length of s
 */
int sslen(char *s)
{
	int len = 0;

	while (*s++)
		len++;
	return (len);
}

/**
 * _mstrcat - concatenates two strings using malloc
 * @str1 : first string
 * @str2 : second string
 * Return: concatenated string
 */
char *_mstrcat(char *str1, char *str2)
{
	int str1_len = sslen(str1);
	int str2_len = sslen(str2);
	int tot_len = str1_len + str2_len + 2;
	int i, j;
	char *cat;

	cat = malloc(tot_len * sizeof(char));
	if (cat == NULL)
		return (NULL);
	for (i = 0; i < str1_len; i++)
	{
		cat[i] = str1[i];
	}
	cat[i] = '/';
	i++;
	for (j = 0; j < str2_len; j++, i++)
	{
		cat[i] = str2[j];
	}
	cat[i] = '\0';

	/*free(str1);*/
	return (cat);
}

/**
 * _which - finds the absolute pathname for a program file
 * @pathname : given filename with or without its full path
 * @dat : pointer to data struct
 * Return: full pathname of program file
 */
char *_which(char *pathname, gvar *dat)
{
	struct stat st;
	char *new_str;
	list_t *tmp;
	list_t *path;


	if (pathname == NULL)
	{
		return (NULL);
	}

	path = path_list();
	tmp = path;

	if (path_depth(pathname) == 0)
	{
		while (path != NULL)
		{
			new_str = _mstrcat(path->str, pathname);
			if (!new_str)
			{
				free_list(tmp);
				return (NULL);
			}

			if (stat(new_str, &st) == 0)
			{
				free_list(tmp);
				dat->newstring_flag = 1;
				return (new_str);
			}
			/*tmp = path;*/
			path = path->next;
			/*free(tmp);*/
			free(new_str);
		}
		free_list(tmp);
		return (pathname);
	}
	if (stat(pathname, &st) == 0)
	{
		free_list(path);
		return (pathname);
	}
	else
	{
		free_list(path);
		return (NULL);
	}
}

/**
 * path_depth - get depth of file
 * @s : given pathname or file
 * Return: depth of path
 */
int path_depth(char *s)
{
	int i = 0, len = 0;

	while (s[i])
	{
		if (s[i] == '/')
			len++;
		i++;
	}
	return (len);
}
/**
 * path_list - builds a list of the path variable
 * Return: list_t list of paths
 */
list_t *path_list(void)
{
	list_t *head, *new, *cur;
	char *tok, *path_val, *path_dup;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);

	path_val = _getenv("PATH");
	if (!path_val || !path_val[0])
		return (NULL);
	path_dup = str_dup(path_val);
	free(path_val);
	if (path_dup == NULL)
	{
		perror("Path_dup");
		free(new);
		return (NULL);
	}
	tok = str_dup(strtok(path_dup, ":"));
	new->str = tok;
	head = new;
	while (tok != NULL)
	{
		cur = malloc(sizeof(list_t));
		if (cur == NULL)
		{
			free(path_dup);
			free_list(head);
			free(tok);
			perror("cur malloc");
			return (NULL);
		}
		tok = str_dup(strtok(NULL, ":"));
		if (tok == NULL)
		{
			break;
		}
		cur->str = tok;
		new->next = cur;
		new = new->next;

	}
	free(cur);
	new->next = NULL;
	free(path_dup);
	return (head);
}
