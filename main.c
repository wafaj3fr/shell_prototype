#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    char *prompt = "The_shell_is_this $";
    char *line = NULL, *cp_line = NULL;
    size_t n = 0;
    ssize_t stread;
    const char *delim = " \n";
    int num_pars = 0;
    char *pars;
    int i, status;
    __pid_t pid;

    (void)ac;

    while (prompt)
    {
        write(1, prompt, _strlen(prompt));
        stread = getline(&line, &n, stdin);

        if (stread == -1)
        {
            write(1, "\n", 1);
            break;
        }

        /*allocate space for copy of cp_line*/
        cp_line = malloc(sizeof(char) * stread);
        if (cp_line == NULL)
        {
            write(1, "tsh: memory allocation error", 28);
            return (-1);
        }

        /*copy line to cp_line*/
        _strcpy(cp_line, line);

        /*split line into array of words*/
        /*calculate number of tokens*/
        pars = strtok(line, delim);

        while (pars != NULL)
        {
            num_pars++;
            pars = strtok(NULL, delim);
        }
        num_pars++;

        /*allocate space to hold the array of strings*/
        argv = malloc(sizeof(char *) * num_pars);
        /*store the pars in the argv array*/
        pars = strtok(cp_line, delim);

        for (i = 0; pars != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * _strlen(pars));

            _strcpy(argv[i], pars);
            pars = strtok(NULL, delim);
        }
        argv[i] = NULL;

        for (i = 0; i <= num_pars; i++)
        {
            const char *str = argv[0];
            int result = _strcmp(str, "exit");
            if (result == 0)
            {
                return (-1);
            }
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return (-1);
        }
        else if (pid == 0)
        {

            execute(argv);
        }
        else
        {
            wait(&status);
        }
    }

    free(cp_line);
    free(line);

    return (0);
}