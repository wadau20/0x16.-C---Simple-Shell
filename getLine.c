#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * input_buff - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *info, char **buf, size_t *len)
{
	ssize_t rat = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rat = getline(buf, &len_p, stdin);
#else
		rat = _getline(info, buf, &len_p);
#endif
		if (rat > 0)
		{
			if ((*buf)[rat - 1] == '\n')
			{
				(*buf)[rat - 1] = '\0'; /* remove trailing newline */
				rat--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = rat;
				info->cmd_buf = buf;
			}
		}
	}
	return (rat);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t in, jar, len;
	ssize_t rat = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rat = input_buff(info, &buf, &len);
	if (rat == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		jar = in; /* init new iterator to current buf position */
		p = buf + in; /* get pointer for return */

		chk_chain(info, buf, &jar, in, len);
		while (jar < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &jar))
				break;
			jar++;
		}

		in = jar + 1; /* increment past nulled ';'' */
		if (in >= len) /* reached end of buffer? */
		{
			in = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (rat); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *in)
{
	ssize_t rat = 0;

	if (*in)
		return (0);
	rat = read(info->readfd, buf, READ_BUF_SIZE);
	if (rat >= 0)
		*in = rat;
	return (rat);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t in, len;
	size_t kk;
	ssize_t rat = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (in == len)
		in = len = 0;

	rat = read_buf(info, buf, &len);
	if (rat == -1 || (rat == 0 && len == 0))
		return (-1);

	c = _strchr(buf + in, '\n');
	kk = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + kk : kk + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + in, kk - in);
	else
		_strncpy(new_p, buf + in, kk - in + 1);

	s += kk - in;
	in = kk;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
