#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

ssize_t custom_getline(char **line, size_t *len, FILE *stream);

/**
 * main - Entry point of the program.
 *
 * Return: 0 on successful execution.
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = custom_getline(&line, &len, stdin)) != -1)
	{
		printf("Line: %s", line);
	}

	free(line); /* Free allocated memory */
	return (0);
}

/**
 * custom_getline - function reads a line from the specified stream
 * and stores it in the provided buffer.
 * @line: Pointer to the character array where the line will be stored.
 * @len: Pointer to the length of the array.
 * @stream: Input stream to read from.
 *
 * Return: the number of characters read (excluding the null terminator)
 * or -1 on failure.
 */

ssize_t custom_getline(char **line, size_t *len, FILE *stream)
{
	if (line == NULL || len == NULL)
	{
		return (-1); /* Invalid arguments */
	}

	if (*line == NULL || *len == 0)
	{
		*line = NULL;
		*len = 0;
	}

	int ch;
	size_t capacity = *len;
	size_t pos = 0;

	while (1)
	{
		ch = fgetc(stream);

		if (ch == EOF || ch == '\n')
		{
			if (ch == EOF && (pos == 0 || ferror(stream)))
			{
				return (-1); /* End-of-file or error */
			}
			break;
		}

		if (pos + 1 >= capacity)
		{
			capacity = (capacity == 0) ? 128 : capacity * 2;
			char *new_line = (char *)realloc(*line, capacity);

			if (new_line == NULL)
			{
				perror("realloc failed");
				return (-1); /* Memory allocation error */
			}
			*line = new_line;
			*len = capacity;
		}

		(*line)[pos++] = ch;
	}

	(*line)[pos] = '\0';

	return (pos);
}
