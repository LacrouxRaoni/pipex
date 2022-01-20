/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:21:14 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/16 11:09:53 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_ptr_count(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\'')
		{
			nb++;
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] != c && s[i] != '\0' && s[i] != '\'')
		{	
			nb++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (nb);
}

static char	**free_tab(char **tab, size_t i)
{
	while ((int)i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

static int	len_space(const char *s, char c, int start)
{
	int	len;

	len = 0;
	if (s[start] == '\'')
	{
		start++;
		while (s[len + start] != '\'' && s[len + start] != 0)
			len++;
	}
	else if (s[start] != c && s[start] != '\'')
	{
		while (s[len + start] != c && s[len + start] != 0)
			len++;
	}
	return (len);
}

static void	mal_sub(char **tab, char const *s, char c, size_t nb_ptr)
{
	size_t	len_ptr;
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	while (i < nb_ptr)
	{
		if (s[start] == c)
			start++;
		else
		{			
			len_ptr = len_space(s, c, start);
			if (s[start] == '\'')
				start++;
			tab[i] = ft_substr(s, start, len_ptr);
			if (tab[i] == NULL)
				free_tab(tab, i);
			start = start + len_ptr;
			i++;
		}
	}
	tab[i] = NULL;
}

char	**split_pipex(char const *s, char c)
{
	char	**tab;
	size_t	nb_ptr;

	if (!s)
		return (NULL);
	nb_ptr = ft_ptr_count(s, c);
	tab = (char **)malloc(((sizeof(char *)) * (nb_ptr + 1)));
	if (!tab)
		return (NULL);
	mal_sub(tab, s, c, nb_ptr);
	return (tab);
}
