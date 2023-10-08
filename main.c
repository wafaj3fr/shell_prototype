#include "main.h"

void execcom(char **argv)
{
    char *com = NULL;

    if (argv)
    {
        com = argv[0];

        if (execve(com, argv, NULL) == -1)
        {
            perror("Error");
        };
    }
}

int main(int ac, char **argv)
{
    char *prompt = "The_shell_is_this $";
    char *linptr = NULL, *cp_linptr = NULL;
    size_t n = 0;
    ssize_t stread;
    const char *delim = " \n";
    int num_pars = 0;
    char *pars;
    int i;
    __pid_t pid;

    (void)ac;

    while (prompt)
    {
        write(1, prompt, strlen(prompt));
        stread = getline(&linptr, &n, stdin);

        if (stread == -1)
        {
            write(1, "\n", 1);
            break;
        }

        /*allocate space for copy of cp_linptr*/
        cp_linptr = malloc(sizeof(char) * stread);
        if (cp_linptr == NULL)
        {
            write(1, "tsh: memory allocation error", 28);
            return (-1);
        }

        /*copy linptr to cp_linptr*/
        strcpy(cp_linptr, linptr);

        /*split linptr into array of words*/
        /*calculate number of tokens*/
        pars = strtok(linptr, delim);

        while (pars != NULL)
        {
            num_pars++;
            pars = strtok(NULL, delim);
        }
        num_pars++;

        /*allocate space to hold the array of strings*/
        argv = malloc(sizeof(char *) * num_pars);
        /*store the pars in the argv array*/
        pars = strtok(cp_linptr, delim);

        for (i = 0; pars != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(pars));

            strcpy(argv[i], pars);
            pars = strtok(NULL, delim);
        }
        argv[i] = NULL;

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return (-1);
        }
        else if (pid == 0)
        {

            execcom(argv);
        }
        else
        {
            int status;
            wait(&status);
        }
    }

    free(cp_linptr);
    free(linptr);

    return (0);
}