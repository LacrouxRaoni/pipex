#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{

	free (pipex->cmd_argv);
	pipex->cmd_argv = NULL;
	free (pipex->path);
	pipex->path = NULL;	
	free (pipex->path_confirmed);
	pipex->path_confirmed = '\0';
}

int	open_files(t_pipex *pipex)
{
	pipex->file1 = open("file1.txt", O_RDONLY);
	if (pipex->file1 < 0)
	{
		write (1, "File can not be opened\n", 24);
		return (1);
	}	
	pipex->file2 = open("file2.txt", O_WRONLY | O_CREAT, 0777);
	if (pipex->file2 < 0)
	{
		write (1, "File can not be opened\n", 24);
		return (1);
	}
	return (0);
}

int		treat_argv_envp(t_pipex *pipex, char **argv, char **envp)
{
	int i;

	pipex->cmd_argv = NULL;
	pipex->path = NULL;
	pipex->path_confirmed = NULL;
	if (argv == NULL || envp == NULL)
	{
		write (1,"Argv or envp is NULL\n", 22);
		return (1);
	}
	pipex->cmd_argv = ft_split(argv[pipex->index], ' ');
	if (pipex->cmd_argv == NULL)
	{	
		write (1, "Argv has returned NULL\n", 24);
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			pipex->path = ft_split(envp[i],':');
		i++;
	}
	return (0);
}

int	check_valid_path_cmd(t_pipex *pipex)
{
	int i;
	char *aux;

	i = 0;
	while (pipex->path[i])
	{
		aux = ft_strjoin("/",pipex->cmd_argv[0]);
		pipex->path_confirmed = ft_strjoin(pipex->path[i], aux);
		if (access(pipex->path_confirmed, F_OK) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	exec_child_process(t_pipex *pipex, int *fd)
{
	close (fd[0]);
	if (pipex->index == 2)
		dup2(pipex->file1, STDIN_FILENO);
	if (pipex->index == 3)
		dup2(pipex->file2, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close (fd[1]);
	if (execve(pipex->path_confirmed,pipex->cmd_argv,NULL) == -1)
		exit(write (1, "execve returned an error\n", 30));
}

void	exec_parent_process(t_pipex *pipex, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	free_pipex(pipex);
	close (fd[0]);
	close (fd[1]);

}


int main (int argc, char **argv, char **envp)
{
	t_pipex pipex;
	int fd[2];
	int pid1;

	pipex.index = 2;
	if (argc == 5)
	{
		while (pipex.index < argc - 1)
		{
			if( open_files(&pipex) == 0 && treat_argv_envp(&pipex, argv, envp) == 0)
			{
				if (check_valid_path_cmd(&pipex) != 0)
					exit (write (1, "Invalid path\n", 14));
				if (pipe(fd) == -1)
					exit (write (1, "Pipe error\n", 14));
				pid1 = fork();
				if (pid1 == -1)
					exit (write (1, "Fork error\n", 14));
				if (pid1 == 0)
					exec_child_process(&pipex, fd);
				waitpid(pid1, NULL, 0);
				exec_parent_process (&pipex, fd);
			}
			else
				exit (write (1, "Pipe error\n", 14));
			pipex.index++;
		}
	}
	else
		exit (write (1, "Invalid argument numbers.\n",27));
	return (0);
}