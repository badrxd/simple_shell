#include "shell.h"

/**
 * _tokening - A function that split & create a full string command.
 * @str: A delimiter for strtok.
 * @buffer: The pointer to input string.
 * Return: A string with the full command.
 */
char **_tokening(char *buffer, const char *str)
{
	char *token = NULL, **cmd = NULL;
	size_t buff_size = 0;
	int i = 0;

	if (buffer == NULL)
		return (NULL);

	buff_size = _strlen(buffer);
	cmd = malloc((buff_size + 1) * sizeof(char *));
	if (cmd == NULL)
	{
		perror("Unable to allocate buffer");
		free(buffer);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, str);
	while (token != NULL)
	{
		cmd[i] = malloc(_strlen(token) + 1);
		if (cmd[i] == NULL)
		{
			perror("Unable to allocate buffer");
			free_all(cmd);
			return (NULL);
		}
		_strcpy(cmd[i], token);
		token = strtok(NULL, str);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
