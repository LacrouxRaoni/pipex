/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:44:50 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/29 13:18:58 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	free_reader(char **backup_buffer, int bytes_read)
{
	free (*backup_buffer);
	return (bytes_read);
}

char	*gnl_join(char **s1, char **s2)
{
	char	*swap;

	swap = *s1;
	*s1 = ft_strjoin((const char *)swap, (const char *)*s2);
	free(swap);
	swap = NULL;
	return (*s1);
}
