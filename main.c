#include "shell.h"

int main()
{
    char command[128];
    while (1)
    {
        prompt();
        input(command, sizeof(command));
        execute(command);
    }
    return 0;
}