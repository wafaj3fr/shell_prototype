#include "main.h"

/**
 * _getenv - gets
 */

char *_getenv(const char *name)
{
    extern char **environ;
    int i;

    for (i = 0; environ[i] != NULL; i++)
    {
        char *key = strtok(environ[i], "=");
        char *value = strtok(NULL, "");
        if (strcmp(key, name) == 0)
        {
            return value;
        }
    }

    return NULL;
}