#ifndef _SHELL_H_
#define _SHELL_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*============     main       ==============*/

int main(int ac, char **av, char **env);
void _prompt(void);
void _handle(int signals);
void _EOF(char *buff);
void exit_shell(char **cmd);

/*============     create_child_pid       ==============*/

void child(char **command, char *name, char **env, int i);
int _change_dir(const char *path);

/*============        Execute       ==============*/

void cmd_execute(char **cmd, char *name, char **env, int i);
void print_env(char **env);
char **_getPATH(char **env);
void msg_error(char *name, int i, char **cmd);

/*============          tokenizing      ==============*/

char **_tokening(char *buffer, const char *str);

/*============     Free the Memory      ==============*/

void free_all(char **cmd);
void free_in_exit(char **cmd);

/*============  Auxiliar_Functions    ==============*/

int _strcmp(char *s1, char *s2);
unsigned int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_strcat(char *dest, char *src);

/*============ END      ==============*/

#endif /* _SHELL_H_ */
