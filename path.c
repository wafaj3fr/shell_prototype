#include "main.h"

/**
 * get_location - gets the location of the executable
 * @command: name of the executable
 * Return: name of the file
 */

char *find_exe(char *command)
{
    char *path, *cp_path, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    path = getenv("PATH");

    if (path)
    {
        /* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/
        cp_path = strdup(path);
        /* Get length of the command that was passed */
        command_length = _strlen(command);

        /* Let's break down the path variable and get all the directories available*/
        path_token = strtok(cp_path, ":");

        while (path_token != NULL)
        {
            /* Get the length of the directory*/
            directory_length = _strlen(path_token);
            /* allocate memory for storing the command name together with the directory name */
            file_path = malloc(command_length + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
            /* to build the path for the command, let's copy the directory path and concatenate the command to it */
            _strcpy(file_path, path_token);
            _strcat(file_path, "/");
            _strcat(file_path, command);
            _strcat(file_path, "\0");

            /* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
            if (stat(file_path, &buffer) == 0)
            {
                /* return value of 0 means success implying that the file_path is valid*/

                /* free up allocated memory before returning your file_path */
                free(cp_path);

                return (file_path);
            }
            else
            {
                /* free up the file_path memory so we can check for another path*/
                free(file_path);
                path_token = strtok(NULL, ":");
            }
        }

        /* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for cp_path */
        free(cp_path);

        /* before we exit without luck, let's see if the command itself is a file_path that exists */
        if (stat(command, &buffer) == 0)
        {
            return (command);
        }

        return (NULL);
    }

    return (NULL);
}