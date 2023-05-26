#include "shell.h"

/**
 * write_history - generate a file or append to existing
 * @info: input structure
 * Return: 1 (Success) -1 (Failure)
 */

int write_history(info_t *info)
{
	list_t *node = NULL;
	ssize_t fd;
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history - reads history
 * @info: input structure
 * Return: histcount (Success) 0 (Otherwise)
 */

int read_history(info_t *info)
{
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);
	int j, last = 0, linecount = 0;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j > fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at _index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * get_history_file - gets history file
 * @info: input structure
 * Return: allocated string with history fil
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));

	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * build_history_list -  add entry to history list
 * @buf: buffer
 * @info: Contains potential args that maintain constant
 * func prototype
 * @linecount: histcount or history linecount
 * Return: always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - renumber the history list after changes
 * @info: Contains potential args that maintain constant
 * func prototype
 * Return: new hist count
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
