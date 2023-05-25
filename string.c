#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: Positive (s1 > s2) Negative (s1 < s2) 0 (s1 == s2)
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 * Return: dest pointer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strlen - length of a string
 * @s: string whose length to check
 * Return: length of string
 */

int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s++)
		j++;

	return (j);
}

/**
 * starts_with - check start of needle is haystack
 * @needle: substring to be found
 * @haystack: string to check
 * Return: next char address of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}
