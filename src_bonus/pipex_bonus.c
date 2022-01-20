/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:17:40 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/19 22:36:22 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_child_process(t_pipex_bonus *pipex, int *fd)
{
	close (fd[0]);
	if (pipex->index == 2)
		dup2(pipex->file1, STDIN_FILENO);
	if (pipex->index == (pipex->new_argc - 2))
		dup2(pipex->file2, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close (fd[1]);
	if (execve(pipex->path_confirmed, pipex->cmd_argv, NULL) == -1)
		exit(write (1, "execve returned an error\n", 30));
}

void	exec_parent_process(t_pipex_bonus *pipex, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	free_pipex(pipex);
	close (fd[0]);
	close (fd[1]);
}

void	prepare_and_exec_pipe(t_pipex_bonus *pipex, int *fd)
{
	int	pid1;

	if (check_valid_path_cmd(pipex) != 0)
	{
		free_pipex (pipex);
		exit (write (1, "Invalid path\n", 14));
	}
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
	exec_parent_process (pipex, fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_bonus	pipex;
	int				fd[2];

	pipex.index = 1;
	if (argc > 2)
	{
		if (ft_strncmp (argv[1], "here_doc", 8) == 0)
			here_doc (fd, &pipex, argv);
		while (++pipex.index < argc - 1)
		{
			if (treat_argv_envp(&pipex, argv, envp) == 0
				&& open_files(&pipex, argv, argc) == 0)
				prepare_and_exec_pipe (&pipex, fd);
			else
			{
				free_pipex(&pipex);
				break ;
			}
		}
	}
	else
		exit (write (1, "Invalid argument numbers\n", 27));
	return (0);
}
