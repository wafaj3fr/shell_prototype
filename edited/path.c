#include "main.h"

/**
 * find_exe - gets the location of the executable
 * @command: name of the executable
 * Return: name of the file
 */

char *find_exe(char *command)
{
    char *path, *path_copy, *dir, *full_path;
    int found = 0;
    int max_path_length = 1024;
    if (command[0] == '/')
    {
        full_path = command;
        return (full_path);
    }
    else
    {
        path = _getenv("PATH");
        if (path == NULL)
        {
            return NULL;
        }

        path_copy = _strdup(path);
        dir = strtok(path_copy, ":");

        full_path = malloc(max_path_length);
        if (full_path == NULL)
        {
            free(path_copy);
            return NULL;
        }

        while (dir != NULL)
        {
            snprintf(full_path, max_path_length, "%s/%s", dir, command);

            if (_strlen(full_path) >= max_path_length)
            {
                max_path_length *= 2;
                free(full_path);
                full_path = malloc(max_path_length);
                if (full_path == NULL)
                {
                    free(path_copy);
                    return NULL;
                }
            }

            if (access(full_path, X_OK) == 0)
            {
                found = 1;
                break;
            }
            dir = strtok(NULL, ":");
        }

        free(path_copy);

        if (found)
        {
            return full_path;
        }
        else
        {
            free(full_path);
            return NULL;
        }
    }
}