#include "shell.h"

/**
 * builtins_list - finds match and execute the associate builtin
 * @data: Program data struct
 * Return: return function executed is there a match found
 * otherwise returns -1
 */

int builtins_list(program_data *data)
{
	int iterator;
	builtins options[] = {
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"env", builtin_env},
		{"exit", builtin_exit},
		{"alias", builtin_alias},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};
	/* walk through the structure */
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/* match found between the given command and a builtin */
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
		/* execute function, and return the return value of the function */
			return (options[iterator].function(data));
		}
		/* if there is no match return -1 */
	}
	return (-1);
}
