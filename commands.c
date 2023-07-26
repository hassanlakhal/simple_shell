#include "main.h"

/**
 * isCommand - Checks if a path is a command.
 *
 * @info: Pointer to the parameter structure.
 * @path: Path to be checked.
 *
 * Return: Depends on the condition.
 */

int isCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * findBuiltin - Finds a built-in command.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: Depends on the condition.
 */

int findBuiltin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myExit},
		{"env", myEnv},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * findCommand - Finds a command in the path.
 *
 * @info: Pointer to the parameter structure.
 */

void findCommand(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->line_count_flag == 1)
	{
		info->line_count++;
		info->line_count_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findPath(info, getEnvVariable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		runCommand(info);
	}
	else
	{
		if ((isInteractiveMode(info) || getEnvVariable(info, "PATH=")
			|| info->argv[0][0] == '/') && isCommand(info, info->argv[0]))
			runCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * runCommand - Executes a command.
 *
 * @info: Pointer to the parameter structure.
 */

void runCommand(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printError(info, "Permission denied\n");
		}
	}
}
