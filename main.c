#include "shell.h"

/**
 * _handle - A function to handle Ctr + C signal.
 * @signals: The signal to handle.
 * Return: Nothing.
 */
void _handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\nShell>> ", 9);
}

/**
 * _prompt - A function that prints the prompt Shell>>
 * Return: Nothing.
 */
void _prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "Shell>> ", 8);
}

/**
 * _EOF - A function that chaecks if buffer is EOF or not
 * @buff: A pointer to the input.
 * Return: Nothing
 */
void _EOF(char *buff)
{
	if (buff)
	{
		free(buff);
		buff = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buff);
	exit(EXIT_SUCCESS);
}

/**
 * exit_shell - It's a function that exits the shell.
 * @cmd: The pointer to tokenizedd command.
 * Return: Nothing.
 */
void exit_shell(char **cmd)
{
	int sta_tus = 0;

	if (cmd[1] == NULL)
	{
		free_all(cmd);
		exit(EXIT_SUCCESS);
	}

	sta_tus = _atoi(cmd[1]);
	free_all(cmd);
	exit(sta_tus);
}

/**
 * main - A function that's runs the shell.
 * @ac: The number of input arguments.
 * @av: A pointer to array of inputed arguments.
 * @env: A pointer to array of the enviromental variables.
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **cmd = NULL;
	size_t buff_size = 0;
	ssize_t chars_nb = 0;
	int i = 0;
	(void)ac;

	while (1)
	{
		i++;
		_prompt();
		signal(SIGINT, _handle);
		chars_nb = getline(&buffer, &buff_size, stdin);
		if (chars_nb == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			cmd = _tokening(buffer, " \0");
			free(buffer);
			if (_strcmp(cmd[0], "exit") != 0)
				exit_shell(cmd);
			else if (_strcmp(cmd[0], "cd") != 0)
				_change_dir(cmd[1]);
			else
				child(cmd, av[0], env, i);
		}
		fflush(stdin);
		buffer = NULL, buff_size = 0;
	}
	if (chars_nb == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
