#include "shell.h"

/**
 * child - The function that creates a sub process.
 * @cmd: The pointer to tokenized cmd
 * @name: The pointer to the name of shell.
 * @env: The pointer to the enviromental variables.
 * @i: Number of executed i.
 * Return: Nothing.
 */
void child(char **cmd, char *name, char **env, int i)
{
	int pid = 0;
	int status = 0;
	int _error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_in_exit(cmd);
	}
	else if (pid == 0)
	{
		cmd_execute(cmd, name, env, i);
		free_all(cmd);
	}
	else
	{
		_error = waitpid(pid, &status, 0);
		if (_error < 0)
		{
			free_in_exit(cmd);
		}
		free_all(cmd);
	}
}

/**
 * _change_dir - Afunction that changes working directory.
 * @path: The new current working directory.
 * Return: 0 on success, -1 on failure.
 */
int _change_dir(const char *path)
{
	char *buff = NULL;
	size_t size = 1024;

	if (path == NULL)
		path = getcwd(buff, size);
	if (chdir(path) == -1)
	{
		perror(path);
		return (98);
	}
	return (1);
}
