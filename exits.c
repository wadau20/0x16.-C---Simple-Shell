#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int in, jar;
	char *s = dest;

	in = 0;
	while (src[in] != '\0' && in < n - 1)
	{
		dest[in] = src[in];
		in++;
	}
	if (in < n)
	{
		jar = in;
		while (jar < n)
		{
			dest[jar] = '\0';
			jar++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int in, jar;
	char *s = dest;

	in = 0;
	jar= 0;
	while (dest[in] != '\0')
		in++;
	while (src[jar] != '\0' && jar < n)
	{
		dest[in] = src[jar];
		in++;
		jar++;
	}
	if (jar < n)
		dest[in] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
