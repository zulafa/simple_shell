#include "shell.h"

/**
 * _strtok - separates strings with delimiters
 * @delim: characters to mark off string in parts
 * @line: array pointer received in getline
 * Return: generated token pointer
 */

char *_strtok(char *delim, char *line)
{
	int i;
	char *copystr;
	static char *str;

	if (line != NULL)
		str = line;

	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
				break;
		}
		if (delim[i] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);

	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
