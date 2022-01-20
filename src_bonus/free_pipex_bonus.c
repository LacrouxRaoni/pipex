/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:12:54 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/13 16:05:14 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pipex(t_pipex_bonus *pipex)
{
	int	i;

	if (pipex->cmd_argv != NULL)
	{
		i = -1;
		while (pipex->cmd_argv[++i])
			free (pipex->cmd_argv[i]);
		free (pipex->cmd_argv);
		pipex->cmd_argv = NULL;
	}
	if (pipex->path != NULL)
	{
		i = -1;
		while (pipex->path[++i])
			free (pipex->path[i]);
		free (pipex->path);
		pipex->path = NULL;
	}
	if (pipex->path_confirmed != NULL)
	{
		free (pipex->path_confirmed);
		pipex->path_confirmed = NULL;
	}
}
