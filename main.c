#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "The_shell_is_this $";
    char *linptr;
    size_t n = 0;
    ssize_t stread;

    (void)ac;

    while (prompt)
    {
        int i;

        write(1, prompt, strlen(prompt));
        stread = getline(&linptr, &n, stdin);

        if (stread == -1)
        {
            write(1, "\n", 1);
            break;
        }
        for (i = 0; argv[i]; i++)
        {
            printf("%s: No such file or directory\n", argv[i]);
        }
    }
    return (0);
}