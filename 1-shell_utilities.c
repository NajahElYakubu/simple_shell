#include "shell.h"
/**
 * ctrl_C - signal
 * @signum: signum
 */
void ctrl_C(int signum)
{
	if (signum == SIGINT)
		print("\n $ ", STDIN_FILENO);
}
/**
 * _getline - takes input from the user
 *
 * Return: the string read
 */
char *_getline(void)
{
	int bufSize = READ_BUF, no_read, position = 0;

	char *buffer = malloc(bufSize * sizeof(char));
	char c;

	if (buffer == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		no_read = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !no_read)
		{
			if (isatty(STDIN_FILENO) == 1)
			{
				print("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !no_read)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;

		if (position >= bufSize)
		{
			bufSize += READ_BUF;
			buffer = _realloc(buffer, READ_BUF, bufSize);
			if (!buffer)
			{
				perror("Failed to reallocate a space in memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int is_delimeter(const char *delimeters, char c);

/**
 * tokenize - split a string
 * @str: string to split
 * @delim: charcter to split str
 * Return: pointer to new or NULL
 */
char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];
	char **arr;

	if (str == NULL || !(*str))
		return (NULL);
	/* calc no of words and lengths */
	for (i = 0; str[i]; i++)
	{
		/* skip delimeters */
		if (is_delimeter(delim, str[i]))
			continue;
		/* get the word length */
		j = i;
		while (!is_delimeter(delim, str[i]) && str[i])
			i++;
		if (i > j)
			lens[size++] = i - j;
		if (!str[i])
			break;
	}
	if (!size)
		return (NULL);
	/* create array of strings */
	arr = malloc((size + 1) * sizeof(char *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;
		/* copy the word */
		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimeter(delim, str[i]) && str[i])
			arr[k][j++] = str[i++];
		arr[k++][j] = '\0';
		if (!str[i])
			break;
	}
	arr[size] = NULL;
	return (arr);
}
/**
 * shell_execute: 
 * @command:
 */
void shell_execute(char **command)
{
	int stat;
	pid_t PID;

	PID = fork();
	if (PID == 0)
	{
		if (execve(command[0], command, NULL) == -1)
		{
			perror("Failed");
			exit(2);
		}
	}
	if (PID < 0)
	{
		perror("failed to call fork");
		exit(1);
	}
	else
		wait(&stat);
}
/**
 * is_delimeter - check if a character is in delimeter
 *
 * @delimeters: pointer to delimeters
 * @c: character to check
 *
 * Return: 1 for true 0 for false
 */
int is_delimeter(const char *delimeters, char c)
{
	int i = 0;

	if (!delimeters)
		return (0);
	while (delimeters[i])
	{
		if (delimeters[i] == c)
			return (1);
		i++;
	}
	return (0);
}
