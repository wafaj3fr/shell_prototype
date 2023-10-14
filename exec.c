#include "main.h"

/**
 * execmd - executes the command
 * @argv: the command to be executed
 */

void execute(char **argv)
{
    char *command = NULL, *actual_command = NULL;

    if (argv)
    {
        /* get the command */
        command = argv[0];

        /* generate the path to this command before passing it to execve */
        actual_command = find_exe(command);

        /* execute the actual command with execve */
        if (execve(actual_command, argv, NULL) == -1)
        {
            perror("Error:");
        }
    }
}