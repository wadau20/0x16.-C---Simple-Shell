#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int in = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[in])
	{
		dest[in] = src[in];
		in++;
	}
	dest[in] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int lengths = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lengths++;
	ret = malloc(sizeof(char) * (lengths + 1));
	if (!ret)
		return (NULL);
	for (lengths++; lengths--;)
		ret[lengths] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int in = 0;

	if (!str)
		return;
	while (str[in] != '\0')
	{
		_putchar(str[in]);
		in++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int in;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(1, buf, in);
		in = 0;
	}
	if (c != BUF_FLUSH)
		buf[in++] = c;
	return (1);
}
