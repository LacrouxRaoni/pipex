/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:08:47 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/30 00:03:46 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(int *fd, t_pipex_bonus *pipex, char **argv)
{
	char	*line;
	int		limiter;

	limiter = ft_strlen(argv[2]);
	if (pipe(fd) < 0)
		exit (write (1, "Pipe error\n", ft_strlen("Pipe error\n")));
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(argv[2], line, limiter) == 0)
		{
			if (line[limiter] == '\n')
				break ;
			else
			{
				write (fd[1], line, ft_strlen(line));
				free (line);
			}
		}
		else
			write (fd[1], line, ft_strlen(line));
		free (line);
	}
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	close (fd[1]);
	pipex->index++;
	free (line);
}
