#include "main.h"

/**
 * execute - executes the command
 * @argv: the command to be executed
 * @path: the path
 */

void execute(char *const *argv, char *path)
{

	if (execve(path, argv, NULL) == -1)
	{
		perror("Error:");
	}
}
