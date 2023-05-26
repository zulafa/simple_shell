#include "shell.h"

/**
 * **strtow - split string to words
 * @d: delimeter string
 * @str: input string
 * Return:  pointer to array of strings or  NULL (Failure
 */

char **strtow(char *str, char *d)
{
	char **s;
	int k, l, m, p, numwords = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (k = 0; str[k] != '\0'; k++)
		if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) || !str[k + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (is_delim(str[k], d))
			k++;
		m = 0;
		while (!is_delim(str[k + m], d) && str[k + m])
			m++;
		s[l] = malloc((m + 1) * sizeof(char));
		if (!s[l])
		{
			for (m = 0; m < l; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}
		for (p = 0; p < m; p++)
			s[l][p] = str[k++];
		s[l][p] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string to words
 * @d: delimeter
 * @str: input string
 * Return: pointer to array of strings or NULL (Failure)
 */


char **strtow2(char *str, char d)
{
	char **s;
	int k, l, m, p, numwords = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		if ((str[k] != d && str[k + 1] == d) ||
				(str[k] != d && !str[k + 1]) || str[k + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (str[k] == d && str[k] != d)
			k++;
		m = 0;
		while (str[k + m] != d && str[k + m] && str[k + m] != d)
			m++;
		s[l] = malloc((m + 1) * sizeof(char));
		if (!s[l])
		{
			for (m = 0; m < l; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}
		for (p = 0; p < m; p++)
			s[l][p] = str[k++];
		s[l][p] = 0;
	}
	s[l] = NULL;
	return (s);
}
