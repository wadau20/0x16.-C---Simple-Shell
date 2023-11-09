#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t jar = *p;

	if (buf[jar] == '|' && buf[jar + 1] == '|')
	{
		buf[jar] = 0;
		jar++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[jar] == '&' && buf[jar + 1] == '&')
	{
		buf[jar] = 0;
		jar++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[jar] == ';') /* found end of this command */
	{
		buf[jar] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = jar;
	return (1);

}

/**
 * chk_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void chk_chain(info_t *info, char *buf, size_t *p, size_t in, size_t len)
{
	size_t jar = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[in] = 0;
			jar = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[in] = 0;
			jar = len;
		}
	}

	*p = jar;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int in;
	list_t *node;
	char *p;

	for (in = 0; in < 10; in++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int in = 0;
	list_t *node;

	for (in = 0; info->argv[in]; in++)
	{
		if (info->argv[in][0] != '$' || !info->argv[in][1])
			continue;

		if (!_strcmp(info->argv[in], "$?"))
		{
			replace_string(&(info->argv[in]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[in], "$$"))
		{
			replace_string(&(info->argv[in]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[in][1], '=');
		if (node)
		{
			replace_string(&(info->argv[in]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[in], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
