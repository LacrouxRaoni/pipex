/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:08:14 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/01/31 11:26:59 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_pipex_bonus
{
	int		index;
	int		file1;
	int		file2;
	int		new_argc;
	int		file_err;
	int		file_exit;
	char	**tmp_envp;
	char	**cmd_argv;
	char	**path;
	char	*path_confirmed;
}	t_pipex_bonus;

int		pipex_bonus(int argc, char **argv, char **envp, t_pipex_bonus *pipex);
int		check_valid_path_cmd(t_pipex_bonus *pipex);
int		treat_argv_envp(t_pipex_bonus *pipex, char **argv, char **envp);
int		validate_path(t_pipex_bonus *pipex, char **envp);
int		open_files(t_pipex_bonus *pipex, char **argv, int argc);
void	free_pipex(t_pipex_bonus *pipex);
void	here_doc(int *fd, t_pipex_bonus *pipex, char **argv);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**split_pipex(char const *s, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
int		free_reader(char **backup_buffer, int bytes_read);
char	*gnl_join(char **s1, char **s2);

#endif