#include "shell.h"

/**
 * execute - execute command with its entire path variables
 * @data: program data pointer
 * Return: 0 (Success) -1 (Otherwise)
 */

int execute(program_data *data)
{
	pid_t pidd;
	int retval = 0, status;

	/* find program in built ins */
	retval = builtins_list(data);
	if (retval != -1)/* if program is found in built ins */
		return (retval);

	/* find program file system */
	retval = find_program(data);
	if (retval)
	{
		/* if program is not found */
		return (retval);
	}
	else
	{
		/* if program is found */
		pidd = fork(); /* create child process */
		if (pidd == -1)
		{
			/* if the fork call fails */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			/* I am the child process, I execute the program */
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
		/* As the father, I wait and study the exit status of the child */
			wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
