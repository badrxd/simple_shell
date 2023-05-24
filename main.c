#include "shell.h"

/**
 * _free_data - frees the data structure.
 *
 * @data_sh: the data structure.
 * Return: no return
 */
void _free_data(data_shell *data_sh)
{
	unsigned int i;

	for (i = 0; data_sh->_environ[i]; i++)
	{
		free(data_sh->_environ[i]);
	}

	free(data_sh->_environ);
	free(data_sh->pid);
}

/**
 * _set_data - Initialize the data structure
 *
 * @data_sh: data structure
 * @av: argument vector
 * Return: no return
 */
void _set_data(data_shell *data_sh, char **av)
{
	unsigned int i;

	data_sh->av = av;
	data_sh->input = NULL;
	data_sh->args = NULL;
	data_sh->status = 0;
	data_sh->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data_sh->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data_sh->_environ[i] = _strdup(environ[i]);
	}

	data_sh->_environ[i] = NULL;
	data_sh->pid = aux_itoa(getpid());
}

/**
 * main - Entry point of shell
 *
 * @ac: args count
 * @av: argst
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void)ac;

	signal(SIGINT, _get_sigint);
	_set_data(&datash, av);
	_shell_loop(&datash);
	_free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
