#include "shell.h"

/**
 * print_list - prints all parts of the list
 * @h: first node pointer
 * Return: list size
 */

size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_len - checks length of the list
 * @h: first node pointer
 * Return: list size
 */

size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - give back array of strings of the list
 * @head: first node pointer
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	char *str;
	char **strs;
	size_t j = list_len(head), k;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);

	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}

/**
 * node_starts_with - gives back a node whose string begins with a prefix
 * @node: list head pointer
 * @prefix: string to match
 * @c: next char to match after prefix
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((c == -1) || (*b == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets index of a node
 * @node: node pointer
 * @head: list head pointer
 * Return: node index or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}

	return (-1);
}
