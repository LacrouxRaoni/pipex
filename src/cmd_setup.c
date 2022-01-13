/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:14:59 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/13 08:39:06 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(t_pipex *pipex, char **argv, int argc)
{
	pipex->file1 = open(argv[1], O_RDONLY);
	if (pipex->file1 < 0)
	{
		write (1, "File 1 can not be opened\n", 26);
		return (1);
	}
	pipex->file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->file2 < 0)
	{
		write (1, "File 2 can not be opened\n", 26);
		return (1);
	}
	return (0);
}

int	validate_path(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			pipex->path = ft_split(envp[i], ':');
		i++;
	}
	return (0);
}

int	treat_argv_envp(t_pipex *pipex, char **argv, char **envp)
{
	pipex->cmd_argv = NULL;
	pipex->path = NULL;
	pipex->path_confirmed = NULL;
	if (argv == NULL || envp == NULL)
	{
		write (1, "Argv or envp is NULL\n", 22);
		return (1);
	}
	pipex->cmd_argv = ft_split(argv[pipex->index], ' ');
	if (pipex->cmd_argv == NULL)
	{	
		write (1, "Argv has returned NULL\n", 24);
		return (1);
	}
	if (validate_path (pipex, envp) == 1)
		return (1);
	return (0);
}

int	check_valid_path_cmd(t_pipex *pipex)
{
	int		i;
	char	*aux;

	if (pipex->cmd_argv[0][0] == '/')
		pipex->path_confirmed = ft_strdup(pipex->cmd_argv[0]);
	if (access(pipex->path_confirmed, F_OK) == 0)
		return (0);
	i = 0;
	while (pipex->path[i])
	{
		aux = ft_strjoin(pipex->path[i], "/");
		pipex->path_confirmed = ft_strjoin(aux, pipex->cmd_argv[0]);
		if (access(pipex->path_confirmed, F_OK) == 0)
		{
			free (aux);
			return (0);
		}
		free (aux);
		free (pipex->path_confirmed);
		pipex->path_confirmed = NULL;
		i++;
	}
	return (1);
}
