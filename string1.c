#include "shell.h"

/**
 * _strcpy - refers to a library function
 * that copies a string.
 * @dest: rep the destination.
 * @src: rep the source of the string.
 *
 * Return: will return a pointer to the destination.
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}
/**
 * _strdup - rep the library function that is used to allocate
 * memory for a new string and copy an existing string into that
 * memory.
 * @str: rep the string that has been allocated to a new location.
 *
 * Return: will return the string that has been allocated.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - rep the input string
 * @str: rep the string that has to be printed.
 *
 * Return: 0
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
			a++;
	}
}

/**
 * _putchar - will output any single character to the
 * console.
 * @c: rep the character that needs to be printed.
 *
 * Return: will return 1 on success and -1 on failure.
 */
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
