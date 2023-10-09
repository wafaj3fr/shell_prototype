#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execcom(char **argv) {
    char *com = NULL;

    if (argv) {
        com = argv[0];

        if (execve(com, argv, NULL) == -1) {
            perror("Error");
            exit(EXIT_FAILURE); // Exit the child process on execve error
        }
    }
}

int main(int ac, char **argv) {
    char *prompt = "The_shell_is_this $";
    char *linptr = NULL, *cp_linptr = NULL;
    size_t n = 0;
    ssize_t stread;
    const char *delim = " \n";
    int num_pars = 0;
    char *pars;
    int i;
    pid_t pid;

    (void)ac;

    while (1) { // Infinite loop
        write(1, prompt, strlen(prompt));
        stread = getline(&linptr, &n, stdin);

        if (stread == -1) {
            if (feof(stdin)) { // Check for EOF (Ctrl+D)
                printf("\nExiting shell...\n");
                break; // Exit the loop gracefully
            } else {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        /* The rest of your code remains the same */

        // Your code to tokenize the input and fork/exec

        /* Free allocated memory */
        free(cp_linptr);
        free(linptr);
        // Free argv array memory here (if you malloc it), before reassigning it
    }

    return 0;
}
