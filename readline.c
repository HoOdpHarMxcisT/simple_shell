#include "vrshell.h"
/**
 * read_line - reads input from stdin
 * @status: current error status number
 * Return: number of characters read
 */
char *read_line(int status)
{
	int chars_read;
	char *buffer = NULL;
	size_t buf_size = 0;

	chars_read = getline(&buffer, &buf_size, stdin);
	if (chars_read == -1)
	{
		if (isatty(0))
			putchar('\n');
		free(buffer);
		exit(status);
	}
	buffer[chars_read - 1] = '\0';
	return (buffer);
}