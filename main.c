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

        /* check for empty lines */
        stread = getline(&line, &n, stdin);
        if (stread == EOF) {
            write(1, "\n", 1);
            exit(0);
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
        if (argv == NULL)
        {
            write(1, "tsh: memory allocation error", 28);
            return (-1);
        }

        /*store the pars in the argv array*/
        pars = strtok(cp_line, delim);

        for (i = 0; pars != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * _strlen(pars));
            if (argv[i] == NULL)
            {
                write(1, "tsh: memory allocation error", 28);
                return (-1);
            }

            _strcpy(argv[i], pars);
            pars = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* check if the command is the exit built-in */
        if (_strcmp(argv[0], "exit") == 0)
        {
            exit(0);
        }

        /* check if the command exists */
        if (access(argv[0], X_OK) != 0)
        {
            // The command does not exist.
            // Print an error message and display the prompt again.
            fprintf(stderr, "tsh: command not found: %s\n", argv[0]);
            continue;
        }

        /* fork the child process */
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

        /* free memory */
        for (i = 0; i < num_pars; i++)
        {
            free(argv[i]);
        }
    }
    free(argv);
    free(cp_line);
    free(line);
    return (0);
}