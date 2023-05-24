#include "shell.h"

/**
 * builtins_env - displays the environment where the shell runs
 * @data: program data struct
 * Return: 0 (Success) other number if declared in the arguments
 */

int builtins_env(program_data *data)
{
	int k;
	char *var_copy = NULL;
	char cpname[50] = {'\0'};

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);

	else
	{
		for (k = 0; data->tokens[1][k]; k++)
		{
			/* check if char exists = */
			if (data->tokens[1][k] == '=')
			{/* check if a var exists with the same name and change its value */
				/* temporarily */
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + k + 1, data);
				/* print the environ */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					/* print variable if it does not exist in environ */
					_print(data->tokens[1]);
					_print("\n");
				}

				else
				{
					/* return old var value */
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
		cpname[k] = data->tokens[1][k];
		}
	errno = 2;
	perror(data->command_name);
	errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..
 * @data: program data struct
 * Return: 0 (Success) or other number if declared in the arguments
 */

int builtin_set_env(program_data *data)
{
	/* validate arguments */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_set_key(data->tokens[1], data->tokens[2], data);
	return (0);
}

/**
 * builtin_unset_env - ..
 * @data: program data struct
 * Return: ..
 */

int builtin_unset_env(program_data *data)
{
	/* validate arguments */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);
	return (0);
}
