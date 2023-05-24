#include "shell.h"

/**
 * tokenize - detaches the string by applying a designed delimiter
 * @data: program data pointer
 * Return: array of the distinct parts of the string
 */

void tokenize(program_data *data)
{
	int a, b, counter = 2, length;
	char *delimiter = " \t";

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}
	for (a = 0; data->input_line[a]; a++)
	{
		for (b = 0; delimiter[b]; b++)
		{
			if (data->input_line[a] == delimiter[b])
				counter++;
		}
	}
	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	a = 0;
	data->tokens[a] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);

	while (data->tokens[a++])
	{
		data->tokens[a] = str_duplicate(_strtok(NULL, delimiter));
	}
}
