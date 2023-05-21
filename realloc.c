#include "shell.h"

/**
 **_memset - this is a function that fills
 * the memory with a constant byte
 * @s: rep the pointer to the memory area
 * @b: rep the byte that will fill *s
 * @n: rep the amount of bytes to be filled.
 * Return: will return a pointer to the memory area
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - will free a string of strings
 * @pp: rep string of strings
 */
void ffree(char **pp)
{
	char **a == pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * _realloc - function that reallocates a block of memory
 * @ptr: rep a pointer to previous malloc'ated block
 * @old_size: rep the byte size of the previous block
 * @new_size: rep the byte size of new block
 *
 * Return: will return a pointer to oldblock.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
