#include "main.h"

/**
 * unsetAlias - Removes an alias.
 *
 * @info: Pointer to the parameter structure.
 * @str: String representing the alias to be removed.
 *
 * Return: 0 if the alias was successfully unset, 1 if there was an error.
*/

int unsetAlias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNode(&(info->alias),
		getNodeIndex(info->alias, nodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - Creates or modifies an alias.
 *
 * @info: Pointer to the parameter structure.
 * @str: String representing the alias to be set.
 *
 * Return: 0 if the alias was successfully set, 1 if there was an error.
*/


int setAlias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (endNode(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Displays an alias.
 *
 * @node: Alias node to be printed.
 *
 * Return: 0 if the alias was successfully printed, 1 if there was an error.
 */

int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * replaceAlias - Replaces aliases in the tokenized string.
 *
 * @info: The parameter structure.
 *
 * Return: 1 if any aliases were replaced, 0 otherwise.
 */

int replaceAlias(info_t *info)
{
	int i = 0;
	list_t *node;
	char *p;

	while (i < 10)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strDuplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
		i++;
	}
	return (1);
}
