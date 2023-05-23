#include "shell.h"

/**
 * _getline - read one line from prompt
 * @data: Program's data struct
 * Return: reading counting bytes
 */

int _getline(program_data *data)
{
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	char buff[BUFFER_SIZE] = {'\0'};
	ssize_t bytes_read, j = 0;

	/* check if there are not more commands in the array */
	/* and checks logical operators */
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
			(array_operators[0] == '|' && errno == 0))
	{
		/* free memory allocated in the array if exists */
		for (j = 0; array_commands[j]; j++)
		{
			free(array_commands[j]);
			array_commands[j] = NULL;
		}

		/* read from file descriptor int to buff */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		j = 0;
		do {
			array_commands[j] = str_duplicate(strtok(j ? NULL : buff, "\n;"));
			/* check and split for && and || operators */
			j = check_logic_ops(array_commands, j, array_operators);
		} while (array_commands[j++]);
	}
	/* obtains the next command (command 0) and remove it for the array */
	data->input_line = array_commands[0];
	for (j = 0; array_commands[j]; j++)
	{
		array_commands[j] = array_commands[j + 1];
		array_operators[j] = array_operators[j + 1];
	}
	return (str_length(data->input_line));
}

/**
 * check_logic_ops - check and split for && and || operators
 * @j: index to be checked in the array_commands
 * @array_commands: array of the commands
 * @array_operators: array of logical operators for each previous command
 * Return: index of last command in the array_commands
 */

int check_logic_ops(char *array_commands[], int j, char array_operators[])
{
	int k;
	char *temp = NULL;

	/* checks for & char in the command line */
	for (k = 0; array_commands[j] != NULL && array_commands[j][k]; k++)
	{
		if (array_commands[j][k] == '&' && array_commands[j][k + 1] == '&')
		{
			/* split the line when chars && was found */
			temp = array_commands[j];
			array_commands[j][k] = '\0';
			array_commands[j] = str_duplicate(array_commands[j]);
			array_commands[j + 1] = str_duplicate(temp + k + 2);
			j++;
			array_operators[j] = '&';
			free(temp);
			k = 0;
		}
		if (array_commands[j][k] == '|' && array_commands[j][k + 1] == '|')
		{
			/* split the line when chars || was found */
			temp = array_commands[j];
			array_commands[j][k] = '\0';
			array_commands[j] = str_duplicate(array_commands[j]);
			array_commands[j + 1] = str_duplicate(temp + k + 2);
			j++;
			array_operators[j] = '&';
			free(temp);
			k = 0;
		}
	}
	return (j);
}
