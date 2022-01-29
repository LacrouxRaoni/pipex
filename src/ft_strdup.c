/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:25:13 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/29 12:12:19 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
