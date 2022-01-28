/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:17:40 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/27 22:53:35 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (execve(pipex->path_confirmed, pipex->cmd_argv, NULL) == -1)
		exit(write (1, "execve returned an error\n", 30));
}

void	exec_parent_process(t_pipex *pipex, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	free_pipex(pipex);
	close (fd[0]);
	close (fd[1]);
}

static	void	exec_pipex(t_pipex *pipex, int *fd, int pid1)
{
	if (pipe(fd) == -1)
	{
		free_pipex (pipex);
		exit (write (1, "Pipe error\n", 14));
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		free_pipex(pipex);
		exit (write (1, "Fork error\n", 14));
	}
	if (pid1 == 0)
		exec_child_process(pipex, fd);
	waitpid(pid1, NULL, 0);
}

static int	prepare_and_exec_pipe(t_pipex *pipex, int *fd, int argc)
{
	int	pid1;

	pid1 = 0;
	if (check_valid_path_cmd(pipex) != 0)
	{
		if (pipex->index == argc - 2)
		{
			free_pipex (pipex);
			write (1, "command not found\n", 19);
			exit (127);
		}
		write (1, pipex->cmd_argv[0], ft_strlen(pipex->cmd_argv[0]));
		write (1, ": command not found\n", 21);
		return (1);
	}
	exec_pipex(pipex, fd, pid1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		fd[2];

	pipex.index = 2;
	if (argc == 5)
	{
		while (pipex.index < argc - 1)
		{
			if (treat_argv_envp(&pipex, argv, envp) == 0
				&& open_files(&pipex, argv, argc) == 0)
			{
				prepare_and_exec_pipe (&pipex, fd, argc);
				exec_parent_process (&pipex, fd);
			}
			else
			{
				free_pipex(&pipex);
				return (1);
			}
			pipex.index++;
		}
	}
	else
		exit (write (1, "Invalid argument numbers\n", 27));
	return (0);
}
