#include "shell.h"

/**
 * bfree - this is a function that will free a pointer
 * and NULLD the address
 * @ptr: rep the address of the pointer to free
 *
 * Return: will return 1 if freed, otherwise will return 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
