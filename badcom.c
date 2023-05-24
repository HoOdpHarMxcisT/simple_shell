#include "vrshell.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * stderr_pc - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int stderr_pc(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
 * print_number - print an int
 * @n: the int to print
 */
void print_number(int n)
{
	int counter, digit;
	int base_ten = 1000000000;
	int skip_zero = 1;
	int min  = -2147483648;
	int was_min = 0;

	counter = 0;
	while (counter < 9)
	{
		/* check for negative int */
		if (n < 0)
		{
			/* add one to min_int to avoid errors*/
			if (n == min)
			{
				n += 1;
				was_min = 1;
			}
			n *= -1;
			stderr_pc('-');
		}
		/* avoids problems when next digit it zero */
		digit = (n / base_ten) % 10;
		/* decrease base_ten until reaches first place */
		if (digit == 0 && skip_zero)
			base_ten /= 10;
		else
		{
			skip_zero = 0;
			stderr_pc(digit + '0');
			base_ten /= 10;
		}
		counter++;
	}
	/* check if num was min_int and add 1 tp output accordingly */
	if (was_min > 0)
		stderr_pc(n % 10 + '1');
	else
		stderr_pc(n % 10 + '0');
}

/**
 * badcom - prints message to stderr
 * @errstatus: error status number
 * @count: number of times the shell has run
 * @cmd: command typed in
 */
void badcom(int errstatus, int count, char *cmd)
{
	int len_colsp;
	char colsp[] = ": ";
	char nf[] = "not found\n";
	char pd[] = "Permission denied\n";
	char *shell;

	shell = _getenv("_");
	write(STDERR_FILENO, shell, _strlen(shell));
	len_colsp = _strlen(colsp);
	write(STDERR_FILENO, colsp, len_colsp);

	print_number(count);
	write(STDERR_FILENO, colsp, len_colsp);

	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, colsp, len_colsp);
	if (errstatus == 127)
		write(STDERR_FILENO, nf, _strlen(nf));
	if (errstatus == 126)
		write(STDERR_FILENO, pd, _strlen(pd));
	free(shell);
}