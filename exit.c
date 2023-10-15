#include "main.h"
void exit_builtin(void)
{
    write(1, "\n", 1);
    exit(0);
}