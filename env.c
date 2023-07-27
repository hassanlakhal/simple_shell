#include "main.h"

/**
 * getEnviron - Retrieves the environment as an array of strings.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: Depends on the condition.
 */

char **getEnviron(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listToStrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * setEnv - Sets an environment variable.
 *
 * @info: Pointer to the parameter structure.
 * @var: Pointer to the variable to be set.
 * @value: Pointer to the value of the variable.
 *
 * Return: Depends on the condition.
 */

int setEnv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && p[0] == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	endNode(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


/**
 * fill_list - Creates a linked list of the environment.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: Depends on the condition.
 */

int fill_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	i = 0;
	while (environ[i])
		endNode(&node, environ[i++], 0);
	info->env = node;
	return (0);
}
