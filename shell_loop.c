#include "shell.h"

/**
 * hsh - main shell loop
 * @info: input structure
 * @av: argument vector from main()
 * Return: 0 (Success) 1 (Error)
 */

int hsh(info_t *info, char **av)
{
	int builtin_ret = 0;
	ssize_t a = 0;

	while (a != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_cmd - locate a command in PATH
 * @info: input structures
 * Return: void
 */

void find_cmd(info_t *info)
{
	int j, n;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (j = 0; n = 0; info->arg[j]; j++)
		if (!is_delim(info->arg[j], " \t\n"))
			n++;
	if (!n)
		return;
	path = find(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - spawn a new thread to run cmd
 * @info: input structure
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: place error function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: place error function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * find_builtin - finds builtin command
 * @info: input structure
 * Return: -2 if builtin signals exit()
 * -1 if builtin not found
 * 0 (Success)
 * 1 (Failure)
 */

int find_builtin(info_t *info)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"cd", _mycd},
		{"help", _myhelp},
		{"env", _myenv},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[j].type; j++)
		if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[j]. func(info);
			break;
		}
	return (built_in_ret);
}
