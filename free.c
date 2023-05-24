#include "shell.h"

/**
 * free_all - A function that frees all memory allocated for the command.
 * @cmd: The pointer to allocated memory to be free.
 * Return: Nothing.
 */
void free_all(char **cmd)
{
	size_t i = 0;

	if (cmd == NULL)
		return;

	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}

	if (cmd[i] == NULL)
		free(cmd[i]);
	free(cmd);
}

/**
 * free_in_exit - A function that frees all the memory allocated and exit.
 * @cmd: A pointer to allocated command memory to free.
 * Return: Nothing.
 */
void free_in_exit(char **cmd)
{
	size_t i = 0;

	if (cmd == NULL)
		return;

	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}

	if (cmd[i] == NULL)
		free(cmd[i]);
	free(cmd);
	exit(EXIT_FAILURE);
}