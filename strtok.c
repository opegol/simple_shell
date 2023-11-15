#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100

/**
 * split_string - Splits a string into an array of words
 * using a specified delimiter.
 *
 * @input_string: The input string to be split into words.
 * @delimiter: The delimiter used to separate words in the input string.
 *
 * Return: A pointer to an array of strings representing
 * the words in the input string.
 *		 The array is terminated with a NULL entry.
 */

char **split_string(const char *input_string, const char *delimiter)
{
	char *token;
	char **words = (char **)malloc(MAX_WORDS * sizeof(char *));

	if (words == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	int word_count = 0;

	/* Using strtok to split the string */
	token = strtok((char *)input_string, delimiter);

	while (token != NULL && word_count < MAX_WORDS)
	{
		words[word_count] = strdup(token);

		if (words[word_count] == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		word_count++;
		token = strtok(NULL, delimiter);
	}

	/* Add a NULL entry at the end to mark the end of the array */
	words[word_count] = NULL;

	return (words);
}

/**
 * main - Entry point for the program
 *
 * Return: 0 on successful execution.
 */

int main(void)
{
	const char *input_str = "This is a sample string.";
	const char *delimiter = " ";

	char **result = split_string(input_str, delimiter);

	/* Print the result */
	for (int i = 0; result[i] != NULL; i++)
	{
		printf("%s\n", result[i]);
		free(result[i]);  /* Free the memory allocated for each word */
	}

	free(result);  /* Free the array of words */

	return (0);
}
