#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - find program in path
 * @data: program data pointer
 * Return: 0 (Success)  errcode if otherwise
 */

int find_program(program_data *data)
{
	char **directories;
	int k = 0, ret_code = 0;

	if (!data->command_name)
		return (2);

	/* if full_path or executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);

	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* search in PATH */
	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (k = 0; directories[k]; k++)
	{
		/* append function_name to path */
		directories[k] = str_concat(directories[k], data->tokens[0]);
		ret_code = check_file(directories[k]);
		if (ret_code == 0 || ret_code == 126)
		{
			/* file found, is not a directory and has execute permissions */
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[k]);
			free_pointers_array(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_pointers_array(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize path in directories
 * @data: program data pointer
 * Return: path directories array
 */

char **tokenize_path(program_data *data)
{
	char *PATH;
	char **tokens = NULL;
	int k = 0;
	int counter_directories = 2;

	/* acquire PATH value */
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		/* path not found */
		return (NULL);
	}

	PATH = str_duplicate(PATH);
	/* check number of directories in PATH */
	for (k = 0; PATH[k]; k++)
	{
		if (PATH[k] == ':')
			counter_directories++;
	}
	/* save space for pointers array */
	tokens = malloc(sizeof(char *) * counter_directories);

	/* tokenize and duplicate every token */
	k = 0;
	tokens[k] = str_duplicate(_strtok(PATH, ":"));

	while (tokens[k++])
	{
		tokens[k] = str_duplicate(_strtok(NULL, ":"));
	}
	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * check_file - checks if file exists, if it is not a directory and if it
 * has execution permission
 * @full_path: full file name pointer
 * Return: 0 (Success) error code if it exists
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/* if file does not exist */
	errno = 127;
	return (127);
}
