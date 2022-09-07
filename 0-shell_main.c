#include "shell.h"

/**
 * main - main body of implementing shell
 * @argc: argument count
 * @argv: variables
 * Return: 1
 */

int main(int argc __attribute__((unused)), char **argv)
{
	data_h var;
	char *line;
	char **args;
	int cmd_type;

	(void) argv;
	var.oldPath = NULL;

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
		cmd_type = check_command(args[0]);
		shell_execute(args, cmd_type, &var);
	}
	return (1);
}
