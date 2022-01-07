# ifndef PIPEX_H
#	define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>


typedef struct s_data_args
{
	char **argv_validator;
	char **new_argv;
	char **new_envp;
	char **path;
	int file1;
	int file2;

}	t_data_args;

# endif