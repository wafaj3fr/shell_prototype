#include "main.h"
void exit_builtin(void)
{
    write(1, "\n", 1);
    exit(0);
}




/* check if the command exists */
int found = 0;
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *dir = strtok(path_copy, ":");

while (dir != NULL) {
    char full_path[PATH_MAX]; // You should include <limits.h> for PATH_MAX
    snprintf(full_path, PATH_MAX, "%s/%s", dir, argv[0]);
    if (access(full_path, X_OK) == 0) {
        found = 1;
        break;
    }
    dir = strtok(NULL, ":");
}

free(path_copy);

if (!found) {
    // The command does not exist in any directory listed in PATH.
    // Print an error message and display the prompt again.
    fprintf(stderr, "tsh: command not found: %s\n", argv[0]);
    continue;
}
