#include "shell.h"

/**
 * print: implemented printf function
 * @var: variable
 * @fd:
 * Return: result
 */
int print(char *var, int fd)
{
	return (write(fd, var, _strlen(var)));
}

void (*get_func(char *command))(char **, data_h *)
{
	int i;

	map_func map[] = {
		{"env", env},
		{"cd", ch_dir},
		{"exit", quit}
	};

	for (i = 0; i < 3; i++)
	{
		if (_strcmp(command, map[i].cmd_name)
				== 0)
			return (map[i].func);
	}
	return (NULL);
}
