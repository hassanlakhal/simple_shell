#include "main.h"

/**
 * myEnv - Prints the current environment.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */

int myEnv(info_t *info)
{
	printListStr(info->env);
	return (0);
}

/**
 * get_env - Gets the value of an environment variable.
 *
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */

char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}



