#include "main.h"

char **tokenize(char *line, const char *delim);
void free_argv(char **argv);
void execute(char **argv);
char *find_exe(char *command);
char *build_path(char *directory, char *command);

int main(int ac, char **av)
{
    char *prompt = "The_shell_is_this $";
    char *line = NULL;
    size_t n = 0;
    ssize_t stread;
    const char *delim = " \t\n";
    char **argv;
    int status;

    (void)ac;
    (void)av;

    while (1)
    {
        printf("%s", prompt);
        stread = getline(&line, &n, stdin);

        if (stread == -1)
        {
            printf("\n");
            break; // Exit the loop on Ctrl+D (EOF)
        }

        // Tokenize the input line into an array of arguments
        argv = tokenize(line, delim);

        // If no arguments are found, continue to the next prompt
        if (argv[0] == NULL) {
            continue;
        }

        // Check if the user entered 'exit' and exit the shell
        if (_strcmp(argv[0], "exit") == 0)
        {
            free(line);
            free_argv(argv);
            break; // Exit the loop
        }

        // Execute the command
        execute(argv);

        // Clean up the allocated memory
        free_argv(argv);
    }

    free(line);

    return 0;
}

void execute(char **argv)
{
    if (argv && argv[0])
    {
        char *command = argv[0];
        char *actual_command = find_exe(command);

        if (actual_command)
        {
            execve(actual_command, argv, NULL);
            perror("Error:");
            exit(EXIT_FAILURE);
        }
        else
        {
            fprintf(stderr, "Command not found: %s\n", command);
            exit(EXIT_FAILURE);
        }
    }
}

char *find_exe(char *command)
{
    char *path = getenv("PATH");
    if (path)
    {
        char *path_copy = strdup(path);
        char *path_token = strtok(path_copy, ":");
        while (path_token)
        {
            char *full_path = build_path(path_token, command);
            if (full_path)
            {
                if (access(full_path, X_OK) == 0)
                {
                    free(path_copy);
                    return full_path;
                }
                free(full_path);
            }
            path_token = strtok(NULL, ":");
        }
        free(path_copy);
    }
    return NULL;
}

char *build_path(char *directory, char *command)
{
    int dir_len = strlen(directory);
    int cmd_len = strlen(command);
    char *full_path = malloc(dir_len + cmd_len + 2);
    if (!full_path)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(full_path, directory);
    strcat(full_path, "/");
    strcat(full_path, command);
    return full_path;
}

char **tokenize(char *line, const char *delim)
{
    char *token;
    int token_count = 0;
    char **tokens = malloc(sizeof(char *));
    if (!tokens)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, delim);
    while (token)
    {
        tokens[token_count] = token;
        token_count++;
        tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
        if (!tokens)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, delim);
    }
    tokens[token_count] = NULL;
    return tokens;
}

void free_argv(char **argv)
{
    if (argv)
    {
        int i = 0;
        while (argv[i])
        {
            free(argv[i]);
            i++;
        }
        free(argv);
    }
}