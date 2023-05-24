#include "shell.h"

/**
 * _without_comment - deletes comments from input
 *
 * @in: input string
 * Return: input without comments
 */
char *_without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * _shell_loop - Loop of the shell
 * @datash: data relevant (av, input, arg)
 *
 * Return: no return.
 */
void _shell_loop(data_shell *datash)
{
	int i, i_eof;
	char *input;

	i = 1;
	while (i == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = _without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			i = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			i = 0;
			free(input);
		}
	}
}
