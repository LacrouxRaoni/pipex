#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		dst[ft_strlen(dst)] = '\0';
		return (ft_strlen(src));
	}
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char		*str;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) < len)
		size = (ft_strlen(s) - start) + 1;
	else
		size = len + 1;
	substr = (char *)malloc(size * sizeof(char));
	if (!substr)
	{
		return (NULL);
	}
	ft_strlcpy(substr, &s[start], size);
	return (substr);
}

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
		if (s[i] != c && s[i] != '\0')
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

static void	mal_sub(char **tab, char const *s, char c, size_t nb_ptr)
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

static int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
	{
		return ((int)n);
	}
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if (s1[i] != s2[i])
		{
			return ((int)(s1[i] - s2[i]));
		}
		i++;
	}
	return (0);
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
//######################################################
//função para destacar a linha PATH e guardarem uma variavel do programa
int	check_envp (t_data_args *args)
{
	int index;

	index = 0;
	while (args->new_envp[index])
	{
		if (ft_strncmp(args->new_envp[index], "PATH=", 5) == 0)
			args->path = ft_split(args->new_envp[index], ':');
		index++;
	}
	return (0);
}

int	check_file (t_data_args *args)
{
	args->file1 = open ("file1.txt", O_RDONLY);
	if (args->file1 < 0)
		return (1);
	args->file2 = open ("file2.txt", O_WRONLY | O_CREAT, 0777);
	if (args->file2 < 0)
		return (1);
	return (0);
}

int	exec_child_process(t_data_args *args)
{
	dup2(args->file1, STDIN_FILENO);
	execve(args->cmd_path, args->argv_validator, NULL);
	return (0);
}

int	exec_pipe(t_data_args *args)
{
	int fd[2];
	int pid1;
	int i;	
	
	args->cmd_path = ft_strdup("");
	i = 0;
	while (args->path_confirmed[args->path_count][i] != '\0')
	{
		args->cmd_path[i] = args->path_confirmed[args->path_count][i];
		i++;
	}
	
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		exec_child_process(args);

	}
	waitpid(pid1, NULL, 0);
	return (0);
}

int		config_cmd(t_data_args *args)
{
	int i;
	char *aux;
	char *aux2;

	args->path_count = 0;
	while (args->argv_validator)
	{
		i = 0;
		while (args->path[i])
		{
			aux2 = ft_strjoin(args->path[i], "/");
			aux = ft_strjoin(aux2, args->argv_validator[args->path_count]);
			if (access(aux, F_OK) == 0)
			{
				args->path_confirmed[args->path_count] = aux;
				exec_pipe(args);
				return (0);
			}
			i++;
		}
		args->argv_validator++;
	}
	return (1);
}


int	pipex (t_data_args *args,char **argv, int argc)
{
		int	index_argc;

		args->new_argv = argv;
		args->argv_validator = NULL;
		index_argc = 2;
		args->path_confirmed = malloc((sizeof(char **)));
		if (!args->path_confirmed)
			return (1);
		while (index_argc < argc - 1)
		{
			args->argv_validator = ft_split(args->new_argv[index_argc], ' ');
			config_cmd(args);
			index_argc++;
		}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_args args;

	if (argc == 5)
	{
		if (envp == NULL)
			return (1);
		args.new_envp = envp;
		if (check_envp (&args) == 0 && check_file (&args) == 0)
			pipex (&args, argv, argc);
		else
			return (1);	
	}
	else
	{
		printf ("invalid number of arguments");
		return (1);
	}
}	