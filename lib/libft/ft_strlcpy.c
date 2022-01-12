/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:28:49 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/11 16:17:02 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	strnlen(const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!dst || !src)
		return (0);
	i = ft_strlen(src);
	if (dst)
	{
		len = strnlen(src, size - 1);
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (i);
}
