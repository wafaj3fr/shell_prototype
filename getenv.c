#include "main.h"

/**
 * _getenv - gets the environment variable path.
 * @name: name of the env.
 */

char *_getenv(const char *name)
{
    extern char **environ;
    int i;
    char *equality, *path_val;

    for (i = 0; environ[i] != NULL; i++)
    {
        equality = strtok(environ[i], "=");
        path_val = strtok(NULL, "");
        if (strcmp(equality, name) == 0)
        {
            return (path_val);
        }
    }

    return NULL;
}