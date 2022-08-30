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
