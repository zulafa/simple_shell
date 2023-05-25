#include "shell.h"

/**
 * _eputs - function that will print an input
 * string
 * @str: rep the string to be printed
 *
 * Return: will return nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - this function will write the character
 * c to stderr
 * @c: rep the character that needs to be printed.
 *
 * Return: will return 1 on success and -1 on failure
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - function tha will write the character c to given fd
 * @c: rep the character that needs to be printed
 * @fd: rep the filedescriptor to write to
 *
 * Return: will return 1 on success, and -1 on failure, and errno
 * is set appropriately
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - function that will print an input string
 * @str: rep the string that nrrds to be printed.
 * @fd: rep the fildescripto to write to
 *
 * Return: will return the number of characters that needs to be
 * inserted.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
