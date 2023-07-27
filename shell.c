#include "main.h"

/**
 * main - Entry point of the program.
 *
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE.
*/

int main(int ac, char **av)
{
	info_t inf[] = {INFO_INIT};
	int fd;

	fd = dup(2);
	if (ac == 2)
	{

		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				write(2,"Error\n",6);
				exit(127);
			} return (1);
		}
		inf->readfd = fd;
	}
	fill_list(inf);
	readHistory(inf);
	exection(inf, av);
	return (0);
}
