/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:08:14 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/31 11:12:39 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_pipex
{
	int		index;
	int		file1;
	int		file2;
	int		flag_cmd;
	int		file_err;
	int		file_exit;
	char	**tmp_envp;
	char	**cmd_argv;
	char	**path;
	char	*path_confirmed;

}	t_pipex;

int		ft_pipex(int argc, char **argv, char **envp, t_pipex *pipex);
int		check_valid_path_cmd(t_pipex *pipex);
int		treat_argv_envp(t_pipex *pipex, char **argv, char **envp);
int		validate_path(t_pipex *pipex, char **envp);
int		open_files(t_pipex *pipex, char **argv, int argc);
void	free_pipex(t_pipex *pipex);
char	**split_pipex(char const *s, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif