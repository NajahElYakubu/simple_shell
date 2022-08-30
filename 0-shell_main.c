#include "shell.h"

/**
 * main - main body of implementing shell
 * @argc: argument count
 * @argv: variables
 * Return: 1
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char *line;
	char **args;
	(void) argv;

	signal(SIGINT, ctrl_C);

	while (1)
	{
		print(" $ ", STDOUT_FILENO);
		line = _getline();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				break;
		}
		args = tokenize(line, DELIM);
		shell_execute(args);
	}
	return (1);
}
