#include "shell.h"

/**
 * print_d - prints a decimal int num of base 10
 * @fd: file descriptor
 * @input: input
 * Return: chars printed
 */

int print_d(int input, int fd)
{
	int k, count = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= k;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * print_error - prints an error message
 * @estr: string with specified error type
 * @info: input structure
 * Return: 0 if no num in string -1 on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * _erratoi - changes a string to an nt
 * @s: string to be changed
 * Return: 0 if no num in string -1 on error
 */

int _erratoi(char *s)
{
	unsigned long int result = 0;
	int k = 0;

	if (*s == '+')
		s++; /* TODO: why does it make main return 255? */

	for (k = 0; s[k] != '\0'; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			result *= 10;
			result += (s[k] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * convert_number - converter function, a clone of itoa
 * @base: base
 * @num: number
 * @flags: argument flags
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	char *ptr;
	char sign = 0;
	static char buffer[50];
	static char *array;
	unsigned long l = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		l = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[l % base];
		l /= base;
	} while (l != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replace first case of '#' with '\0'
 * @buf: address of the string to be modified
 * Return: always 0
 */

void remove_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
