/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:37:44 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/11 13:00:41 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ptr_count(char const *s, char c)
{
	size_t	i;

	if (!*s)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

static	char *strsubsep(char *str, char sub, char delim)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] != delim)
	{
		if (str[i] != delim)
			str[j++] = str[i];
		if (str[i] == delim && str[i + 1] != delim)
			if (j > 0 && i < len - 1)
				str[j++] = sub;
		i++;
	}
	str[j] = '\0';
	return (str);
}

static void	free_tab(char **tab, size_t size)
{
	size_t i;

	i = -1;
	while (++i < size)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

static void	mal_sub(char **tab, char *str, size_t nb_ptr, char delim)
{
	size_t	i;

	str = strsubsep(str, '\0', delim);
	i = -1;
	while (++i < (nb_ptr - 1))
	{
		tab[i] = ft_strdup(str);
		if (!tab[i])
		{
			free_tab(tab, i);
			return ;
		}
		str += ft_strlen(str) + 1;
	}
	tab[i] = NULL;
}


char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	size_t	nb_ptr;

	if (!s)
		return (NULL);
	str = strsubsep(ft_strdup(s), c, c);
	if (!str)
		return (NULL); 
	nb_ptr = ft_ptr_count(s, c) + 1;
	tab = (char **)malloc(sizeof(char *) * nb_ptr);
	if (!tab)
		return (NULL);
	mal_sub(tab, str, nb_ptr, c);
	free (str);
	return (tab);
}
