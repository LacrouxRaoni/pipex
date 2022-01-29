/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:25:13 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/29 13:18:24 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strdup(const char *s)
{
	char		*str;
	size_t		len;

	len = ft_strlen(s) + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, len);
	return (str);
}
