#include "main.h"

/**
 * execmd - executes the command
 * @argv: the command to be executed
 */

void execute(char **argv, char *pathname)
{
    /* execute the actual command with execve */
    if (execve(pathname, argv, NULL) == -1)
    {
        perror("Error:");
    }
}