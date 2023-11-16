#include "main.h"

int builtin_cmd_handler(char **token, char *line, gvar *dat);
int cmd_arr_len(char **built_in_cmd);
int cd_h(char *str, gvar *dat);
int env_h(void);
int exit_h(char **token, char *line, gvar *dat);

/**
 * builtin_cmd_handler - handles the built-in commands of the shell
 * @token : array of tokenised commands
 * @line : command line input
 * @dat : pointer to data struct
 * Return: 0 on success
 */
int builtin_cmd_handler(char **token, char *line, gvar *dat)
{
	int i, arr_len, cmd_type = 0;
	char *built_in_cmd[] = {"cd", "env", "exit", "setenv", "unsetenv", NULL};

	arr_len = cmd_arr_len(built_in_cmd);

	if (!token[0])
		return (-1);

	for (i = 0; i < arr_len; i++)
	{
		if (_strcmp(token[0], built_in_cmd[i]) == 0)
		{
			cmd_type = i + 1;
			break;
		}
	}

	switch (cmd_type)
	{
		case 1:
			cd_h(token[1], dat);
			break;

		case 2:
			env_h();
			break;

		case 3:
			exit_h(token, line, dat);
			break;

		case 4:
			_setenv(token[1], token[2], 1);
			break;

		case 5:
			_unsetenv(token[1]);
			break;

		default:
			return (-1);
	}
	return (0);
}

/**
 * cmd_arr_len - returns the number of array elements
 * @built_in_cmd : array to check
 * Return: Number of elements in array
 */
int cmd_arr_len(char **built_in_cmd)
{
	int i = 0, len = 0;

	while (built_in_cmd[i])
	{
		len++;
		i++;
	}
	return (len);
}

/**
 * cd_h  - handler for 'cd'
 * @str : pathname string
 * @dat : pointer to data struct
 * Return: 0 on success, -1 otherwise
 */
int cd_h(char *str, gvar *dat)
{

	int ret;
	char *old_cwd = _getenv("OLDPWD");
	char *home, *pwd;
	char *new_cwd;

	home = _getenv("HOME");
	if (str == NULL)
	{
		ret = chdir(home);
	}
	else if (_strcmp(str, "-") == 0)
	{
		ret = chdir(old_cwd);

	}
	else if (_strcmp(str, "") == 0)
	{
		ret = chdir(home);
	}

	else
		ret = chdir(str);

	if (ret == -1)
	{
		print_err_msg(&str, 3, dat);
		free(home);
		free(old_cwd);
		return (-1);
	}
	else if (ret == 0)
	{
		pwd = _getenv("PWD");
		new_cwd = getcwd(NULL, 0);
		_setenv("OLDPWD", pwd, 1);
		_setenv("PWD", new_cwd, 1);
		/*(free(new_cwd);*/
	}
	if (str != NULL && str[0] == '-' && str[1] != '-')
	{
		write(1, new_cwd, slen(new_cwd));
		write(1, "\n", 1);
	}
	free(home);
	free(pwd);
	free(new_cwd);
	free(old_cwd);
	return (ret);
}

/**
 * env_h - handler for 'env' to print the environment
 * Return: 0 on success
 */
int env_h(void)
{
	int i = 0;

	if (!environ)
		return (-1);

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], slen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);

		i++;
	}
	return (0);
}

/**
 * exit_h - handler for 'exit' to exit from the shell
 * @token : array containing program name and exit status
 * @line : command line input
 * @dat : pointer to data struct
 * Return: exit status
 */
int exit_h(char **token, char *line, gvar *dat)
{
	unsigned int i = 0, n = 0;

	if (!token[1])
	{
		free(token);
		free(line);
		fre_env();
		if (dat->exec_hist == 1)
			exit(0);
		else
			exit(2);
	}
	while (token[1][i])
	{
		/*printf("token[1]: %s\n", token[1]);*/
		if (token[1][i] >= '0' && token[1][i] <= '9')
		{
			n = (10 * n) + (token[1][i] - '0');
			/*printf("t[1][i]: %c\n", token[1][i]);*/
			i++;
		}
		else
		{
			n = (print_err_msg(token, 2, dat));
			break;
		}
	}
	/*printf("n: %i\n", n);*/

	free(token);
	free(line);
	fre_env();
	exit(n);
}
