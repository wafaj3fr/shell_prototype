#include "main.h"

/**
 * execmd - executes the command
 * @argv: the command to be executed
 */

void execute(char *const *argv, char *path)
{

    if (execve(path, argv, NULL) == -1)
    {
        perror("Error:");
    }
}