#include "main.h"

char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/**
 * _getenv - return value environment parameter
 * @name : environment parameter whose value will be retieved
 * Return: retrieved value
 */

char *_getenv(const char *name)
{
	int i = 0, j, k = 0;
	int buf_len;
	char *val;

	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '\0' || name[j] != '\0')
		{
			if (environ[i][j] != name[j] && environ[i][j] != '=')
			{
				break;
			}
			else if (environ[i][j] == '=' && !name[j])
			{
				buf_len = (slen(environ[i]) - j);
				val = malloc(buf_len * sizeof(char) + 1);

				while (environ[i][j++])
					val[k++] = environ[i][j];
				val[buf_len] = '\0';
				return (val);
			}
			else if (environ[i][j] != name[j])
				break;

			j++;
		}
		i++;
	}
	return (NULL);
}

/**
 * _setenv - sets an environment variable
 * @name : name of variable to set
 * @value : value of variable to set
 * @overwrite : determines whether the value of an
 *		existing varible should be overwritten or not
 * Return: 0 on success, and -1 otherwise
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	/*extern char **environ;*/
	int i = 0, j, l, m, val_len, name_len;
	char *env_var;

	if (value == NULL)
		return (-1);

	val_len = slen(value);
	name_len = slen(name);
	env_var = malloc((val_len + name_len + 2) * sizeof(char));
	if (env_var == NULL)
	{
		perror("malloc");
		return (-1);
	}
	for (l = 0; l < name_len; l++)
	{
		env_var[l] = name[l];
	}
	env_var[name_len] = '=';
	for (m = 0; m <= val_len; m++)
	{
		env_var[name_len + m + 1] = value[m];
	}
	env_var[name_len + val_len + 1] = '\0';

	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '\0' || name[j] != '\0')
		{
			if (environ[i][j] != name[j] && environ[i][j] != '=')
				break;
			else if (environ[i][j] == '=' && !name[j])
			{
				if (overwrite != 0)
				{
					free(environ[i]);
					environ[i] = env_var;
					return (0);
				}
			}
			else if (environ[i][j] != name[j])
				break;
			j++;
		}
		i++;
	}
	free(environ[i]);
	environ[i] = env_var;
	environ[i + 1] = NULL;

	return (0);
}


/**
 * _unsetenv - deletes an environment variable
 * @name : name of envionment variable to delete
 * Return: 0 on success, and -1 otherwise
 */
int _unsetenv(const char *name)
{
	/*extern char **environ;*/
	int i = 0, j;

	if (!name)
		return (-1);


	while (environ[i])
	{
		j = 0;

		while (environ[i][j] != '\0' || name[j] != '\0')
		{
			if (environ[i][j] != name[j] && environ[i][j] != '=')
			{
				break;
			}
			else if (environ[i][j] == '=' && !name[j])
			{
				free(environ[i]);
				environ[i] = NULL;
				return (0);
			}
			else if (environ[i][j] != name[j])
				break;
			j++;
		}
		i++;
	}

	return (0);
}
