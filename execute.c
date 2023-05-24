#include "shell.h"

/**
 * cmd_execute - the function that executes a command.
 * @cmd: The pointer to tokienizing command
 * @name: The name of the shell.
 * @env: The pointer to the enviromental variables.
 * @i: Number of executed cicles.
 * Return: Nothing.
 */
void cmd_execute(char **cmd, char *name, char **env, int i)
{
	char **path_ways = NULL, *full_path = NULL;
	struct stat st;
	unsigned int j = 0;

	if (_strcmp(cmd[0], "env") != 0)
		print_env(env);
	if (stat(cmd[0], &st) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			perror(name);
			free_in_exit(cmd);
		}
	}
	else
	{
		path_ways = _getPATH(env);
		while (path_ways[j])
		{
			full_path = _strcat(path_ways[j], cmd[0]);
			j++;
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, cmd, env) < 0)
				{
					perror(name);
					free_all(path_ways);
					free_in_exit(cmd);
				}
				return;
			}
		}
		msg_error(name, i, cmd);
		free_all(path_ways);
	}
}

/**
 * print_env - A function that prints all enviromental variables.
 * @env: The pointer to enviromental variables.
 * Return: Nothing.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;

	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * _getPATH - A function to gets the full value from.
 * enviromental variable PATH.
 * @env: The pointer to enviromental variables.
 * Return: All tokenized pathways for commands.
 */
char **_getPATH(char **env)
{
	char *pathvalue = NULL, **path_ways = NULL;
	unsigned int i = 0;

	pathvalue = strtok(env[i], "=");
	while (env[i])
	{
		if (_strcmp(pathvalue, "PATH"))
		{
			pathvalue = strtok(NULL, "\n");
			path_ways = _tokening(pathvalue, ":");
			return (path_ways);
		}
		i++;
		pathvalue = strtok(env[i], "=");
	}
	return (NULL);
}

/**
 * msg_error - the function that prints message not found.
 * @name: The name of the shell.
 * @i: Number of cicles.
 * @cmd: The pointer to tokenized command.
 * Return: Nothing.
 */
void msg_error(char *name, int i, char **cmd)
{
	char c;

	c = i + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd[0], _strlen(cmd[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
