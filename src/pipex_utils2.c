#include "pipex.h"

size_t	ft_ptr_count(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{	
			nb++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (nb);
}

char	**free_tab(char **tab, size_t i)
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

void	mal_sub(char **tab, char const *s, char c, size_t nb_ptr)
{
	size_t	len_ptr;
	size_t	i;

	i = 0;
	while (i < nb_ptr)
	{
		if (*s == c)
			s++;
		else if (*s != c)
		{
			len_ptr = 0;
			while (s[len_ptr] != c && s[len_ptr] != 0)
				len_ptr++;
			tab[i] = ft_substr(s, 0, len_ptr);
			if (tab[i] == NULL)
				free_tab(tab, i);
			s = s + len_ptr;
			i++;
		}
	}
	tab[i] = NULL;
}


char	**ft_split(char const *s, char c)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (!s3)
	{
		return (NULL);
	}
	ft_strlcpy(s3, s1, len_s1 + 1);
	ft_strlcpy(&s3[len_s1], s2, len_s2 + 1);
	return (s3);
}
