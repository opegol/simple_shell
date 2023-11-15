#include "main.h"

char **stok(char *str);
int execute(char **token, gvar *dat);
void sig_h(int arg);
void free_arr(char **str);
int main(int ac, char **av);

/**
 * stok - returns an array of string tokens
 * @str : given string
 * Return: array of string tokens
 */
char **stok(char *str)
{
	char *s;
	char **tok;
	int i = 0;

	s = strtok(str, "\n ");
	tok = malloc(1024 * sizeof(char));
	if (tok == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	tok[i] = s;
	while (s)
	{
		i++;
		s = strtok(NULL, "\n ");
		*(tok + i) = s;
	}
	return (tok);
}

/**
 * execute - handles processess
 * @token : array of stings represntig commands and options
 * @dat : pointer to a data struct
 * Return: 0 on success, and -1 otheerwise
 */
int execute(char **token, gvar *dat)
{
	pid_t cp;
	int status;
	char *fullpath;
	int retn = 0;

	fullpath = _which(token[0], dat);

	if (!token[0] || (access(fullpath, F_OK) == -1))
	{
		if (errno == EACCES)
			retn = print_err_msg(token, 126, dat);
		else
			retn = print_err_msg(token, 127, dat);
		return (retn);
	}


	if (fullpath)
	{
		cp = fork();

		if (cp == -1)
		{
			perror("Error");
			return (-1);
		}

		if (cp == 0)
		{
			retn = execve(fullpath, token, environ);
			if (retn == -1)
			{
				if (errno == EACCES)
					retn = print_err_msg(token, 126, dat);
				else
					perror("Error");
			}
			/*free(fullpath);*/
			exit(retn);
		}

		else
		{
			wait(&status);
			retn = WEXITSTATUS(status);
		}
	}

	else
	{
		perror("Error");
	}
	if (dat->newstring_flag == 1)
	{
		free(fullpath);
		dat->newstring_flag = 0;
	}
	return (retn);
}

/**
 * free_arr - free array
 * @str : given array string
 */
void free_arr(char **str)
{
	int i = 0;

	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
	}
	free(str);
	str = NULL;
}

/**
 *  sig_h - handles ctrl c signal
 *  @arg : argument to print -unused
 */
void sig_h(int arg __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - simple shell program
 * @ac : number of program arguments
 * @av : array of program arguments as strings
 * Return: 0 Always
 */
int main(int ac, char **av)
{
	ssize_t gc = 1;
	char *line = NULL;
	size_t n = 0;
	char **token;
	char *prompt = "$ ";
	int ret = 0;
	gvar vars, *dat = &vars;

	dat->newstring_flag = 0;	/*relevant in _which(), execute() -> free()*/
	dat->prog_name = av[0];
	dat->exec_hist = 0;
	/*pn = &gc;*/

	environ = env_copy();
	if (environ == NULL)
		exit(-1);

	signal(SIGINT, sig_h);

	if (isatty(STDIN_FILENO) && ac == 1)
	{
		while (gc > 0)
		{
			write(STDOUT_FILENO, prompt, 2);
			gc = getline(&line, &n, stdin);

			if (gc == -1)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}

			token = stok(line);
			dat->exec_hist++;
			ret = builtin_cmd_handler(token, line, dat)
			if (ret < 0)
				ret = execute(token, dat);
			free(token);
			free(line);
		}

	}
	else if (!(isatty(STDIN_FILENO)))
	{
		while ((gc = getline(&line, &n, stdin)) != -1)
		{
			dat->exec_hist++;
			token = stok(line);
			if (token[0] == NULL)
			{
				free(token);
				continue;
			}
			ret = builtin_cmd_handler(token, line, dat);
			if (ret < 0)
			{
				ret = execute(token, dat);
			}
			free(token);
		}
	}
	free(line);
	fre_env();
	return (ret);
}
