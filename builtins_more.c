#include "shell.h"

/**
 * builtin_exit - program exit with status
 * @data: program data struct
 * Return: 0 (Success) or other number if declared in the arguments
 */

int builtin_exit(program_data *data)
{
	int j;

	if (data->tokens[1] != NULL)
	{
		/* if arg for exit exists, check if it is a number */
		for (j = 0; data->tokens[1][j]; j++)
			if ((data->tokens[1][j] < '0' || data->tokens[1][j] > '9')
					&& data->tokens[1][j] != '+')
			{
				/* if it is not a number */
				errno = 2;
				return (2);
			}
		errno = _atoi(data->okens[1];
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - change current directory
 * @data: program data struct
 * Return: 0(Success) or other number if declared in the arguments
 */

int builtin_cd(program_data *data)
{
	int error_code = 0;
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");
			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);
		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set work directory
 * @data: program data struct
 * @new_dir: new directory
 * Return: 0 (Success) or other number if declared in arguments
 */

int set_work_directory(program_data *data)
{
	int err_code = 0;
	char old_dir[128] = {0};

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDWD", old_dir, data);

	return (0);
}

/**
 * builtin_alias - add, remove or display aliases
 * @data: program data struct
 * Return: 0 (Success) or other num if declared in the arguments
 */

int builtin_alias(program_data *data)
{
	int j = 0;

	/* no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));
	while (data->tokens[++j])
	{
		/* arguments present, print every env variable */
		if (count_characters(data->tokens[j], "="))
			set_alias(data->tokens[j], data);
		else
			print_alias(data, data->tokens[j]);
	}
	return (0);
}

/**
 * builtin_help - displays environment where shell runs
 * @data: program data struct
 * Return: 0 (Success) or other number if declared in arguments
 */

int builtin_help(program_data *data)
{
	char *mensajes[6] = {NULL};
	int j, length = 0;

	mensajes[0] = HELP_MSG;

	/* validate arguments */
	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_UNSETENV_MSG;
	mensajes[4] = HELP_SETENV_MSG;
	mensajes[5] = HELP_CD_MSG;
	for (j = 0; mensajes[j]; j++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[j], length))
		{
			_print(mensajes[j] + length + 1);
			return (1);
		}
	}
	/* if no match, print error and return -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}
