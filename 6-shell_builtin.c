#include "shell.h"

void env(char **command __attribute__((unused)), data_h *h __attribute__((unused)))
{
	int i = 0;

	while (environ[i])
	{
		print(environ[i++], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

void quit(char **command, data_h *var)
{
	(void) command;
	(void) var;
}
#define SETPWD(V) (V = strdup(_getenv("OLDPWD")))
void ch_dir(char **command, data_h *var)
{
	char *home;

	home = _getenv("HOME");
	if (command[1] == NULL)
	{
		SETPWD(var->oldPath);
		if (chdir(home) < 0)
			exit(EXIT_FAILURE);
	}
	if (strcmp(command[1], "-") == 0)
	{
		if (var->oldPath == NULL)
		{
			SETPWD(var ->oldPath);
			if (chdir(home) < 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			SETPWD(var->oldPath);
			if (chdir(var->oldPath) < 0)
				exit(EXIT_FAILURE);
		}
	}
	else
	{
		SETPWD(var->oldPath);
		if (chdir(command[1]) < 0)
			exit(EXIT_FAILURE);
	}
}

#undef GETPWD
