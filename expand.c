#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: pointer to program data struct
 * Return: Nothing, but sets errno
 */

void expand_variables(program_data *data)
{
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;
	int k, l;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);
	for (k = 0; line[k]; k++)
		if (line[k] == '#')
			line[k--] = '\0';

		else if (line[k] == '$' && line[k + 1] == '?')
		{
			line[k] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + k + 2);
		}

		else if (line[k] == '$' && line[k + 1] == '$')
		{
			line[k] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + k + 2);
		}

		else if (line[k] == '$' && (line[k + 1] == ' ' || line[k + 1] == '\0'))
			continue;

		else if (line[k] == '$')
		{
			for (l = 1; line[k  + l] && line[k + l] != ' '; l++)
				expansion[l - 1] = line[k + l];
			temp = env_get_key(expansion, data);
			line[k] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + k + l);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
	free(data->input_line);
	data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expand aliases
 * @data: pointer to program data struct
 * Return: Nothing but sets errno
 */

void expand_alias(program_data *data)
{
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;
	int k, l, was_expanded = 0;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);
	for (k = 0; line[k]; k++)
	{
		for (l = 0; line[k + l] && line[k + l] != ' '; l++)
			expansion[l] = line[k + l];
		expansion[l] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + k + l);
			line[k] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at buffer end
 * @str_to_add: string to be copied in buffer
 * @buffer: buffer to be filled
 * Return: Nothing but sets errno
 */

int buffer_add(char *str_to_add, char *buffer)
{
	int length, k;

	length = str_length(buffer);
	for (k = 0; str_to_add[k]; k++)
	{
		buffer[length + k] = str_to_add[k];
	}
	buffer[length + k] = '\0';
	return (length + k);
}
