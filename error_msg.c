#include "main.h"

char *build_err_msg(char **token, char *msg, int err_num, gvar *dat);
int print_err_msg(char **token, int err_num, gvar *dat);
char *itostr(int n);
/**
 * build_err_msg - strings together a custom error message
 * @token : tokenized command line input
 * @msg : core error message to display
 * @err_num : error number
 * @dat : pointer to data struct
 * Return: custom error message
 */
char *build_err_msg(char **token, char *msg, int err_num, gvar *dat)
{
	char *err, *exh_str, *cmd, *tmp, *prog_name;
	int len;
	char *sep = ": ";

	prog_name = dat->prog_name;

	cmd = token[0];
	if (err_num == 2)
		cmd = token[1];
	if (!cmd)
		return (NULL);
	exh_str = itostr(dat->exec_hist);
	if (!exh_str)
		return (NULL);
	if (err_num == 3 || err_num == 2)
		len = slen(prog_name) + slen(cmd) + slen(exh_str) + slen(msg) + 10;
	else
		len = slen(prog_name) + slen(cmd) + slen(exh_str) + slen(msg) + 7;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(exh_str);
		return (NULL);
	}
	/*err[len] = '\0';*/
	_strcpy(err, prog_name);
	_strcat(err, sep);
	_strcat(err, exh_str);
	_strcat(err, sep);
	if (err_num == 3)
	{
		tmp = cmd;
		cmd = "cd";
	}
	else if (err_num == 2)
	{
		tmp = cmd;
		cmd = "exit";
	}
	_strcat(err, cmd);
	_strcat(err, sep);
	_strcat(err, msg);
	if (err_num == 3 || err_num == 2)
	{
		_strcat(err, tmp);
		_strcat(err, "\n");
	}


	free(exh_str);
	return (err);
}

/**
 * print_err_msg - prints custom error messages
 * @token : tokenized command line input
 * @err_num : number identifing type of error generated
 * @dat : pointer to data struct
 * Return: error number err_num
 */
int print_err_msg(char **token, int err_num, gvar *dat)
{
	char *err_msg;

	if (!token[0])
		return (-1);

	if (err_num == 2)
		err_msg = build_err_msg(token, "Illegal number: ", 2, dat);
	else if (err_num == 3)
		err_msg = build_err_msg(token, "can't cd to ", 3, dat);
	else if (err_num == 126)
		err_msg = build_err_msg(token, "Permission denied\n", 126, dat);
	else if (err_num == 127)
	{
		err_msg = build_err_msg(token, "not found\n", 127, dat);
	}
	write(STDERR_FILENO, err_msg, slen(err_msg));
	free(err_msg);
	return (err_num);
}

/**
 * itostr - convert int to string
 * @n : integer to convert
 * Return: string buffer
 */

char *itostr(int n)
{
	int flag = 1, len = 1, num;
	char *buf;

	if (n < 0)
	{
		num = n * -1;
		len++;
		flag = -1;
	}
	else
		num = n;
	while (num > 9)
	{
		num /= 10;
		len++;
	}
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);

	buf[len] = '\0';

	if (flag == -1)
		buf[0] = '-';
	len--;
	do {
		buf[len] = (num % 10) + '0';
		num /= 10;
		len--;
	} while (num > 0);
	return (buf);
}
