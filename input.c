#include "shell.h"

void input(char *command, size_t size)
{
    if (fgets(command, size, stdin) == NULL)
    {
        if (feof(stdin))
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
    }
    command[strcspn(command, "\n")] = '\0';
}