#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *find_exe(char *command);
void execute(char *const *argv, char *path);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
char *_getenv(const char *name);
void print_environment();


char **tokenize_line(char *line);
void free_tokens(char **tokens);

#endif
