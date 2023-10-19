#include "main.h"

/**
 * main - Entry point
 * @ac: arguments count
 * @argv: arguments
 * Return: 0 for success
 */

int main(int ac, char **argv)
{
    char *line = NULL, *backup_line = NULL, *pars, *pathval;
    size_t n = 0;
    ssize_t stread;
    const char *delim = " \n";
    int num_pars, i, status;
    pid_t pid;

    (void)ac;

    while (1)
    {
        num_pars = 0;
        
        dollar_prpmpt();

        /* check for empty lines */
        stread = getline(&line, &n, stdin);
        if (stread == EOF)
        {
            write(1, "\n", 1);
            exit(0);
        }

        /*allocate space for copy of cp_line*/
        backup_line = malloc(sizeof(char) * stread);
        if (backup_line == NULL)
        {
            write(1, "tsh: memory allocation error", 28);
            return (-1);
        }

        /*copy line to cp_line*/
        _strcpy(backup_line, line);

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
        pars = strtok(backup_line, delim);

        for (i = 0; pars != NULL; i++)
        {
            argv[i] = malloc(_strlen(pars) + 1);
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
        if (_strcmp(line, "exit") == 0)
        {
            free(backup_line);
            free(line);
            exit(0);
        }
        else if (_strcmp(line, "\n") == 0)
        {
            continue;
        }
        else if (_strcmp(line, "env") == 0)
        {
            print_environment();
        }

        pathval = find_exe(line);

        /* check if the command exists */
        if (access(pathval, X_OK) == 0)
        {
            pid = fork();

            if (pid == -1)
            {
                perror("fork");
                return (-1);
            }
            else if (pid == 0)
            {
                execute(argv, pathval);
            }
            else
            {
                wait(&status);
            }
        }
        else
        {
            write(1, "Command not found\n",19);
        }
    }

    for (i = 0; i < num_pars; i++)
    {
        free(argv[i]);
    }
    free(pathval);
    free(backup_line);
    free(line);
    free(argv);

    return (0);
}