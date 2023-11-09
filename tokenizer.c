#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int in, jar, kk, mn, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (in = 0; str[in] != '\0'; in++)
		if (!is_delim(str[in], d) && (is_delim(str[in + 1], d) || !str[in + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (in = 0, jar = 0; jar < numwords; jar++)
	{
		while (is_delim(str[in], d))
			in++;
		kk = 0;
		while (!is_delim(str[in + kk], d) && str[in + kk])
			kk++;
		s[jar] = malloc((kk + 1) * sizeof(char));
		if (!s[jar])
		{
			for (kk = 0; kk < jar; kk++)
				free(s[kk]);
			free(s);
			return (NULL);
		}
		for (mn = 0; mn < kk; mn++)
			s[jar][mn] = str[in++];
		s[jar][mn] = 0;
	}
	s[jar] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int in, jar, kk, mn, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (in = 0; str[in] != '\0'; in++)
		if ((str[in] != d && str[in + 1] == d) ||
		    (str[in] != d && !str[in + 1]) || str[in + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (in = 0, jar = 0; jar < numwords; jar++)
	{
		while (str[in] == d && str[in] != d)
			in++;
		kk = 0;
		while (str[in + kk] != d && str[in + kk] && str[in + kk] != d)
			kk++;
		s[jar] = malloc((kk + 1) * sizeof(char));
		if (!s[jar])
		{
			for (kk = 0; kk < jar; kk++)
				free(s[kk]);
			free(s);
			return (NULL);
		}
		for (mn = 0; mn < kk; mn++)
			s[jar][mn] = str[in++];
		s[jar][mn] = 0;
	}
	s[jar] = NULL;
	return (s);
}
