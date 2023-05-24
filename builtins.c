#include "shell.h"
/**
  * checkbi - check if argument is a builtin
  * @tokens: tokens from parsed string
  *
  * Return: 0 if builtin
  */
int checkbi(char **tokens)
{
	if (_strncmp(tokens[0], "exit", 4) == 0)
		return (0);
	if (_strncmp(tokens[0], "env", 3) == 0)
		return (0);
	return (-1);
}
/**
  * runbi - run builtin
  * @tokens: tokens from parsed string
  *
  * Return: 1 if successful
  */
int runbi(char **tokens)
{
	int i = 0;
	int i2 = 0;

	if (_strncmp(tokens[0], "env", 3) == 0)
	{
		if (environ == NULL)
		{
			free_dptr(tokens);
			return (1);
		}
		while (environ[i] != NULL)
		{
			while (environ[i][i2] != '\0')
			{
				_putchar(environ[i][i2]);
				i2++;
			}
			_putchar('\n');
			i++;
			i2 = 0;
		}
		free_dptr(tokens);
	}
	else if (_strncmp(tokens[0], "exit", 4) == 0)
	{
		free_dptr(tokens);
		return (0);
	}
	return (1);
}