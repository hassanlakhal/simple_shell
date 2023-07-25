#include "main.h"

/**
 * _print_illegal_num - print illegal number message
 * @prog_name: name of program
 * @cmd: command
 * @arg: argument of exit
 * Return: Nothing (void function)
 */
void _print_illegal_num(char *prog_name, char *cmd, char *arg)
{
	write(STDERR_FILENO, prog_name, _strlen(prog_name));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": Illegal number: ", 18);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * _print_not_found - print not found message if
 * command is not found
 * @prog_name: name of program
 * @cmd: command
 * Return: Nothing (void function)
 */
void _print_not_found(char *prog_name, char *cmd)
{
	write(STDERR_FILENO, prog_name, _strlen(prog_name));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * _puts - Prints a string followed by newline
 * @s: string to print
 * Return: Nothing (void function).
 */
void _puts(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
	_putchar('\n');
}

/**
 * _sputs - Prints a string
 * @s: string to print
 * Return: Nothing (void function).
 */
void _sputs(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

