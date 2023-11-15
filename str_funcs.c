#include "main.h"

int slen(const char *s);
int _strcmp(char *s1, char *s2);
char *str_dup(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

/**
 * slen - gets length of string
 * @s : given string
 * Return: string length
 */
int slen(const char *s)
{
	int len = 0, i = 0;

	while (s[i])
	{
		len++;
		i++;
	}
	return (len);
}

/**
 * _strcmp - compares two strings.
 * @s1 : first string
 * @s2 : string to compare
 *
 * Return: an int greater than 0 if s1 > s2,
 *		0 if equal, and an int < 0 if less than.
 */
int _strcmp(char *s1, char *s2)
{

	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);

}

/**
 * str_dup - duplicates string
 * @str : given string
 * Return: new string
 */
char *str_dup(char *str)
{
	int i = 0;
	char *new_str;

	if (str == NULL)
		return (NULL);

	new_str = malloc(sizeof(char) * slen(str) + 1);
	if (new_str == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/**
 * _strcat - This function appends the src string to the dest string
 * @dest : base string
 * @src : string to append
 * Return: Pointer to concatenated string @dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int len = 0;
	int j;

	while (*(dest + i))
	{
		i++;
		++len;
	}

	for (j = 0; *(src + j); j++)
		*(dest + len + j) = *(src + j);
	*(dest + len + j) = '\0';

	return (dest);
}

/**
 * _strcpy - copies the string pointed to by src
 *		to the buffer pointed to by dest.
 * @dest : buffer to copy string to
 * @src : pointer to string to copy
 *
 * Return: pointer to @dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
