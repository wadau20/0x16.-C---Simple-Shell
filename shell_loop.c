#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t rat = 0;
	int builtin_rets = 0;

	while (rat != -1 && builtin_rets != -2)
	{
		clear_info(info);
		if (interact(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rat = get_input(info);
		if (rat != -1)
		{
			set_info(info, av);
			builtin_rets = find_builtin(info);
			if (builtin_rets == -1)
				find_command(info);
		}
		else if (interact(info))
			_putchar('\n');
		free_inf(info, 0);
	}
	write_history(info);
	free_inf(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_rets == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rets);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int in, built_in_rets = -1;
	builtin_table builtintbl[] = {
		{"exit", _myex},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhist},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (in = 0; builtintbl[in].type; in++)
		if (_strcmp(info->argv[0], builtintbl[in].type) == 0)
		{
			info->line_count++;
			built_in_rets = builtintbl[in].func(info);
			break;
		}
	return (built_in_rets);
}

/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int in, kk;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (in = 0, kk = 0; info->arg[in]; in++)
		if (!is_delim(info->arg[in], " \t\n"))
			kk++;
	if (!kk)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t childs_pids;

	childs_pids = fork();
	if (childs_pids == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childs_pids == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_inf(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
