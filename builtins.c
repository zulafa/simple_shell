#include "shell.h"

/**
 * _myexit - rep exit shell
 * @info: Contains potential args that maintain constant
 * func prototype
 * Return: 0 when info.argv[0] != "exit"
 */

int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{/* in presence of an exit argument */
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "illegal num: ");
			_eputs(info->argv[1];
			_eputchar('\n');
			return (1);
		}

		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * _myhelp - changes current working directory
 * @info: Contains potential args that maintain constant
 * func prototype
 * Return: Always 0
 */

int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function yet to be implemented \n");

	if (0)
		_puts(*arg_array); /*temp att_unused workaround */
	return (0);
}

/**
 * _mycd - changes current working directory
 * @info: Contains potential args that maintain constant
 * func prototype
 * Return: Always 0
 */

int _mycd(info_t *info)
{
	int chdir_ret;
	char *s, dir, buffer[1024];

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should it be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putcharr('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should it be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "cannot cd to");
		_eputs(info->argv[1], _eputchar('\n');
	}
	else
	{
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
