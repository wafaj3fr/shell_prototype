#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

char *find_exe(char *command);
void execute(char **argv, char *pathname);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
char *_strdup(char *str);
void exit_builtin(void);
char *_getenv(const char *name);

#endif
