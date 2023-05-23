#include "shell.h"
/**
* main - this function runs a simple UNIX command interpreter.
*
* Return: this return is the value of the last executed command.
*/
char *_strtok (char *buff)
{
	return (strtok (buff, " \t\n"));
}
int main()
{
	char *buff = NULL, *cmd, **arr_cmd;
	size_t buff_size = 0;
	int nb_ch = 0, status, i = 0;
	pid_t child_pid;

	while (1)
	{
		arr_cmd = malloc(sizeof(char *)* 1036);
		if (!arr_cmd)
			perror("Alocated space non");
		write(1,"$ ",2);
		nb_ch = getline(&buff, &buff_size, stdin);
		if (nb_ch == -1)
			perror("shell");
		cmd = _strtok(buff);
		while (cmd)
		{
			arr_cmd[i] = cmd;
			cmd = strtok (NULL, " \t\n");
			i++;
		}
		arr_cmd[i] = NULL;
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(arr_cmd[0], arr_cmd, NULL) == -1)
				perror("./shell");
		}
		else
			wait(&status);
		free(arr_cmd);
		i = 0;
	}
	return(0);
}
