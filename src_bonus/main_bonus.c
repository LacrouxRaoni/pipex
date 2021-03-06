/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:32:24 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/31 11:27:04 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex_bonus	pipex;

	pipex.file_exit = 0;
	pipex.index = 1;
	if (pipex_bonus(argc, argv, envp, &pipex) == 1)
		return (1);
	if (pipex.file_exit == 1)
		exit (1);
	return (0);
}
