#include "vrshell.h"

/**
 * _strcat - concatenates two strings
 * @dest: string appended to
 * @src: string appened to dest
 *
 * Return: the concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int counter, dest_index;

	dest_index = 0;
	while (dest[dest_index] != '\0')
		dest_index++;

	counter = 0;
	while (src[counter] != '\0')
	{
		dest[dest_index] = src[counter];
		dest_index++;
		counter++;
	}

	dest[dest_index] = '\0';
	return (dest);
}

/**
 * _strlen - get length of string
 * @str: string to process
 *
 * Return: length of str
 */
int _strlen(char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
		count++;

	return (count);
}

/**
 * _strncmp - compares 2 strings
 * @s1: first string to compare
 * @s2: second string to compare
 * @n: number of chars to compare
 *
 * Return: negative, zero, or positive
 */
int _strncmp(char *s1, char *s2, int n)
{
	int index = 0;
	int sum = 0;

	while (index < n)
	{
		if (s1[index] == s2[index])
			index++;
		else
		{
			sum = s1[index] - s2[index];
			break;
		}
	}

	return (sum);
}

/**
 * _strncpy - copies a string
 * @dest: the destination of the copy
 * @src: the source of the copy
 * @from: where to start copying from
 * @n: n bytes to copy
 *
 * Return: the copied string
 */
char *_strncpy(char *dest, char *src, int from, int n)
{
	int count = 0;

	while (count < n)
	{
		dest[count] = src[from];
		from++;
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

/**
 * _strdup - mallocs and copies a new string
 * @s: string to duplicate
 *
 * Return: duplicated string, NULL if malloc fails
 */

char *_strdup(char *s)
{
	int len;
	char *dupe;

	if (s == NULL)
		return (NULL);

	len = _strlen(s);
	dupe = malloc(sizeof(char) * (len + 1));
	if (dupe == NULL)
		return (NULL);

	_strncpy(dupe, s, 0, len);
	return (dupe);
}