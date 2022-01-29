/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:20:00 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/29 13:18:38 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
