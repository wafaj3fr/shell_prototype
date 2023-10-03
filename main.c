#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "AWshell $";
    char *lineptr;
    size_t n = 0;
    size_t str_read;

    /*declaring void variables*/
    (void)ac;
    (void)argv;

    while (prompt)
    {
        printf("%s", prompt);
        getline(&lineptr, &n, stdin);
        printf("%s\n", lineptr);
    }
    free(lineptr);
    return (0);
}
