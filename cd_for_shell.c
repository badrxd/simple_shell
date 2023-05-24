#include "shell.h"

/**
 * _cd_shell - changes the current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int _cd_shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		_cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		_cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		_cd_dot(datash);
		return (1);
	}

	_cd_to(datash);

	return (1);
}
