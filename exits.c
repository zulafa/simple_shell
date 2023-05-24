#include "shell.h"

/**
 **_strncpy - refers to a C library
 * function that is used to copy a string
 * @dest: rep the detsination in which the string is going
 * to be copied to.
 * @src: rep the source of the string.
 * @n: rep the number of chracters that are going
 * to be copied.
 * Return: will always return the concatentated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && i < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (i < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - C library function used to conatenate
 * strings
 * @dest: rep the destination of the first string
 * @src: rep the source of the second string.
 * @n: rep the number of characters that are going
 * to be used.
 * Return: will return the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
	dest[a] = src[b];
a++;
b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}
/**
 **_strchr - C library function that is used to
 * find the occurence of a character in a string.
 * @s: rep the string to be parsed.
 * @c: rep the character that is essentally in search.
 * Return: will return (s) to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
