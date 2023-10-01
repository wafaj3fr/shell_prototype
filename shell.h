#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void prompt();
void input(char *command, size_t size);
void execute(char command);

#endif