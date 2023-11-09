#include "shell.h"
#include <stdlib.h>
#include <stdio.h>	
/**
 * interact - returns true if shell is interact mode
 * @info: struct address
 *
 * Return: 1 if interact mode, 0 otherwise
 */
int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
		else
			return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int in, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (in = 0;  s[in] != '\0' && flag != 2; in++)
	{
		if (s[in] == '-')
			sign *= -1;

		if (s[in] >= '0' && s[in] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[in] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
