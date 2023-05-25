#include "shell.h"

/**
 * is_chain - function used to test if the current character in
 * the buffer is a chain delimeter.
 * @info: rep the parameter struct
 * @buf: rep the character buffer
 * @p: rep the address of the current position in buf
 *
 * Return: will return 1 if its a chain delimeter, and 0 otherwis
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
			{
			buf[a] = 0;
			info->cmd_buf_type = CMD_CHAIN;
			}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - function that will checl if we need to proceed
 * chaining based on last status.
 * @info: rep the parameter struct
 * @buf: rep the character buffer.
 * @p: rep the address of the current position in buf
 * @i: rep the starting position in buf
 * @len: rep the length of the buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	*p = a;
}

/**
 * replace_alias - function that is responsible for replacing an alias in the tokenized string
 * @info: rep the parameter struct
 *
 * Return: will return 1 if replaced, and 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - this is a function that replaces vars in the tokenized string
 * @info: rep the parameter struct
 *
 * Return: will return 1 if its replaced, and 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - function that will replace a string.
 * @old: rep the address of the old string.
 * @new: rep the new string
 *
 * Return: will return 1 if replaced, and 0 otherwise
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
