#include "main.h"

/*char *_getenv(const char *name);*/
/*int _setenv(const char *name, const char *value, int overwrite);*/
/*int _unsetenv(const char *name);*/

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
