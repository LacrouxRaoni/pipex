/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:07:46 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/31 11:16:22 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.file_exit = 0;
	pipex.index = 2;
	if (ft_pipex(argc, argv, envp, &pipex) == 1)
		return (1);
	if (pipex.file_exit == 1)
		exit (1);
	return (0);
}
