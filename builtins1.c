#include "shell.h"

/**
 * _myhistory - shows history list, every command by line, preceded
 * by line num, starting with 0
 * @info: Contains potential args that maintain constant
 * func prototype
 * Return: always 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * set_alias - sets alias to string
 * @str: string alias
 * @info: input structure
 * Return: 0 (Success) 1 (Failure)
 */

int set_alias(info_t *info, char *str)
{
	char *i;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	if (!**i)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * unset_alias - sets alias to string
 * @str: string alias
 * @info: input structure
 * Return: 0 (Success) 1 (Failure)
 */

int unset_alias(info_t *info, char *str)
{
	cint ret;
	char *i, n;

	i = strchr(str, "-");
	if  (!i)
		return (1);
	n = *i;
	*i = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_start_with(info->alias, str, -1)));

	*i = n;
	return (ret);
}

/**
 * print_alias - prints alias string
 * @node: alias node
 * Return: 0 (Success) 1 (Failure)
 */

int print_alias(list_t *node)
{
	char *i = NULL, *k = NULL;

	if (node)
	{
		i = _strchr(node->str, '=');
		for (k = node->str; k <= i; k++)
			_putchar(*k);

		_putchar('\'');
		_puts(i + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - imitates alias builtin
 * @info: Contains potential args that maintain constant
 * func prototype
 * Return: always 0
 */

int _myalias(info_t *info)
{
	char *i = NULL;
	int j = 0;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		i = _strchr(info->argv[j], '=');
		if (i)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_start_with(info->alias, info->argv[j], '='));
	}
	return (0);
}
