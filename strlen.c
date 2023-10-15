#include "main.h"

/**
 * _strlen - returns the length of a string.
 * @s: string to be calculated
 * Return: length of the string
 */

int _strlen(char *s)
{
    int len = 0;
    int i;

    for (i = 0; s[i] != '\0'; i++)
    {
        len++;
    }

    return (len);
}