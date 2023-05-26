#include "shell.h"

/**
 * get_input - get line minus new line
 * @info: input structure
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	ssize_t a = 0;
	static size_t k, l, len;
	static char *buf; /* command chain buffer */
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &len);
	if (a == -1) /*EOF */
		return (-1);
	if (len)	/* other commands left in the chain buffer */
	{
		l = k;
		p = buf + 1; /* get return pointer */
		check_chain(info, buf, &l, k, len);

		while (l < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}
		k = l + 1;
		if (k >= len) /* at end of buffer */
		{
			k = len = 0; /* reset length and position */
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p)); /* return length of current command */
	}
	*buf_p = buf; /* not a chain, pass back buffer from _getline() */
	return (a);
}

/**
 * read_buf - reads buffer
 * @buf: buffer
 * @info: input structure
 * @s: size
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *s)
{
	ssize_t r = 0;

	if (*s)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
		*s = r;

	return (r);
}

/**
 * input_buf - buffers chained commands
 * @buf: buffer address
 * @len: len var address
 * @info: input structure
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t len_p = 0;
	ssize_t a = 0;

	if (!*len)
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &len_p, stdin);
#else
		a = _getline(info, buf, &len_p);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0'; /* erase trailing newline */
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is it a command chain? */
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * sigintHandler - bar ctrl-C
 * @sig_num: signal number
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * _getline - get next line from standard input
 * @length: size of preallocated ptr buffer if not NULL
 * @ptr: pointer to buffer address
 * @info: input structure
 * Return: b
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	size_t j;
	ssize_t r = 0, b = 0;
	static size_t l, len;
	static char buf[READ_BUF_SIZE];
	char *p = NULL, *new_p = NULL, *k;

	p = *ptr;
	if (p && length)
		b = *length;
	if (l == len)
		l = len = 0;
	r = read_buf(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	k = _strchr(buf + l, '\n');
	j = k ? 1 + (unsigned int)(k - buf) : len;
	new_p = realloc(p, b, b ? b + j : j + 1);

	if (!new_p) /* malloc fail */
		return (p ? free(p), -1 : -1);
	if (b)
		_strncat(new_p, buf + l, j - 1);
	else
		_strncpy(new_p, buf + l, j - 1 + 1);

	b += j - l;
	l = j;
	p = new_p;

	if (length)
		*length = b;
	*ptr = p;

	return (b);
}
