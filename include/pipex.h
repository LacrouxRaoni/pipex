/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:08:14 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/11 18:20:34 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		index;
	int		file1;
	int		file2;
	char	**tmp_envp;
	char	**cmd_argv;
	char	**path;
	char	*path_confirmed;

}	t_pipex;

int		check_valid_path_cmd(t_pipex *pipex);
int		treat_argv_envp(t_pipex *pipex, char **argv, char **envp);
int		validate_path(t_pipex *pipex, char **envp);
int		open_files(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_ptr_count(char const *s, char c);
char	**free_tab(char **tab, size_t i);
void	mal_sub(char **tab, char const *s, char c, size_t nb_ptr);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif