#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUF 1000
#define DELIM "  \a\t\r\n"

void ctrl_C(int);
char *_getline(void);
char **tokenize(char *, const char *);
void shell_execute(char **);


int print(char *, int);

int _strlen(char *);
void *_realloc(void *, int, int);
#endif
