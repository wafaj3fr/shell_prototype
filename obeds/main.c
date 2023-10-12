#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "(Eshell) $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    int status;
    pid_t pid;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1)
    {
        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (nchars_read == -1)
        {
            printf("Exiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy lineptr to lineptr_copy */
        _strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * _strlen(token));
            _strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        for (i = 0; i <= num_tokens; i++)
        {
            const char *str = argv[0];
            int result = strcmp(str, "exit");
            if (result == 0)
            {
                return (-1);
            }
        }

        if ((pid = fork()) > 0)
        {
            // Parent process
            wait(&status);
            printf("Process terminated with status = %d\n", status);
        }
        else if (pid == 0)
        {
            execmd(argv);
        }
        else
        {
            perror("fork");
            exit(1);
        }
    }
    free(lineptr_copy);
    free(lineptr);

    return (0);
}