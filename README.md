# shell_prototype

This is a representation of a simple shell that replicates a linux based shell

## The shell

The shell is a command-line interface that acts as an intermediary between a user and the operating system. Its primary function is to interpret and execute user commands.

## How the shell works

### The following explains the process or steps that a shell goes through

- Displaying the prompt.
- Reading user input.
- Parsing the command. (Tokenization)
- Searching the command. (PATH)
- Creating a child process. (fork)
- Executing the command. (exec)
- Wait for the command completetion.
- Displaying output.
- Returning to the prompt.
- Exiting the shell.

## Content of this repository

- The header file that contains function prototypes.
- A function that displays the prompt.
- A function that reads user input.
- A function that executes commands.
- A main source code file that is an entry point.

## main source file

```#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "The_shell_is_this $";
    char *linptr;
    size_t n = 0;
    ssize_t stread;

    (void)ac;

    while (prompt)
    {
        int i;

        write(1, prompt, strlen(prompt));
        stread = getline(&linptr, &n, stdin);

        if (stread == -1)
        {
            write(1, "\n", 1);
            break;
        }
        for (i = 0; argv[i]; i++)
        {
            printf("%s: No such file or directory\n", argv[i]);
        }
    }
    return (0);
}
```
