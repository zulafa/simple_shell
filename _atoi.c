#include "shell.h"

/**
 * interactive - prompts the user for input,
 * then processes it in real time.
 * @info: rep the struct address.
 *
 * Return: will return 1 if the shell is in interactive
 * mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - will check if the character in place is a delimeter.
 * @c: rep the char that needs to be checked.
 * @delim: rep the delimeter string.
 * Return: rep 1 if its true , and 0 if it false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - function that will check if the
 * alphabet involved is present.
 * @c: rep the character to be inputted.
 * Return: will return 1 if c is an alphabet,
 * 0 otherwise.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			return (1);
			else
			return (0);
			}

/**
 * _atoi - function that is responsible for converting a string
 * to an interger.
 * @s: rep the string that needs to be converted.
 * Return: will return 0 if their is no numbers in string.
 */

int _atoi(char *s)
{
int a, sign = 1, flag = 0, output;
unsigned int result = 0;

for (a = 0; s[a] != '\0' && flag != 2; a++)
{
	if (s[a] == '-')
		sign *= -1;

	if (s[a] >= '0' && s[a] <= '9')
	{
		flag = 1;
		result *= 10;
		result += (s[a] - '0');
	}
	else if (flag == 1)
		flag = 2;
}

if (sign == -1)
	output = -result;
	else
	output = result;

	return (output);
	}
