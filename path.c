#include "main.h"
/**
 * find_exe - find exe file if found.
 * @command: exe file name or path.
 * Return: NULL if fail, full_path if seccuse.
 */
char *find_exe(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	int found = 0;
	size_t max_path_length = 1024;

	if (command[0] == '/')
	{
		full_path = command;
		return (full_path);
	}

	while (*command == ' ' || *command == '\t')
	{
		command++;
	}
	path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	full_path = malloc(max_path_length);
	if (full_path == NULL)
	{
		free(path_copy);
		free(full_path);
		return (NULL);
	}

	while (dir != NULL)
	{
		snprintf(full_path, max_path_length, "%s/%s", dir, command);

		if (strlen(full_path) >= max_path_length)
		{
			max_path_length *= 2;
			free(full_path);
			full_path = malloc(max_path_length);
			if (full_path == NULL)
			{
				free(path_copy);
				free(full_path);
				return (NULL);
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
		return (full_path);
	}
	else
	{
		free(full_path);
		return (NULL);
	}
}
/**
 * print_environment - prints the env var.
 * Return: NULL.
 */
void print_environment(void)
{
	extern char **environ;

	char **env = environ;
	while (*env)
	{
		write(1, *env, _strlen(*env));
		write(1, "\n", 2);
		env++;
	}
}

/**
 * dollar_prpmpt - prints the prompt.
 * Return: NULL.
 */
void dollar_prpmpt(void)
{
	char *prompt = "$ ";

	write(1, prompt, _strlen(prompt));
}
