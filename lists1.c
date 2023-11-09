#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *hh)
{
	size_t in = 0;

	while (hh)
	{
		hh = hh->next;
		in++;
	}
	return (in);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t in = list_len(head), jar;
	char **strs;
	char *str;

	if (!head || !in)
		return (NULL);
	strs = malloc(sizeof(char *) * (in + 1));
	if (!strs)
		return (NULL);
	for (in = 0; node; node = node->next, in++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (jar = 0; jar < in; jar++)
				free(strs[jar]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[in] = str;
	}
	strs[in] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *hh)
{
	size_t in = 0;

	while (hh)
	{
		_puts(convert_number(hh->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hh->str ? hh->str : "(nil)");
		_puts("\n");
		hh = hh->next;
		in++;
	}
	return (in);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t in = 0;

	while (head)
	{
		if (head == node)
			return (in);
		head = head->next;
		in++;
	}
	return (-1);
}
