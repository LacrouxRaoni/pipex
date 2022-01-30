# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 16:17:34 by rruiz-la          #+#    #+#              #
#    Updated: 2022/01/30 16:36:12 by rruiz-la         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
NAME_BONUS	=	pipex_bonus

I_PIPEX	=	-I ./include

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC_DIR	=	src
SRC_FILES	=	pipex.c \
				cmd_setup.c \
				split_pipex.c \
				free_pipex.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_substr.c \
				ft_strncmp.c

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC_DIR_BONUS	=	src_bonus
SRC_FILES_BONUS	=	main_bonus.c \
					pipex_bonus.c \
					cmd_setup_bonus.c \
					split_pipex_bonus.c \
					free_pipex_bonus.c \
					here_doc_bonus.c \
					ft_strdup_bonus.c \
					ft_strjoin_bonus.c \
					ft_strlcpy_bonus.c \
					ft_strlen_bonus.c \
					ft_substr_bonus.c \
					ft_strncmp_bonus.c \
					get_next_line_bonus.c \
					get_next_line_utils_bonus.c

SRC_BONUS	=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJ_DIR = obj
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR_BONUS = obj_bonus
OBJ_BONUS	=	$(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

FS	=	-g3

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(FS) $(OBJ) -o $(NAME) $(I_PIPEX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

bonus: $(NAME_BONUS)

$(NAME_BONUS):	$(OBJ_DIR_BONUS) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(I_PIPEX)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(OBJ_DIR):
	mkdir obj

$(OBJ_DIR_BONUS):
	mkdir obj_bonus

clean: 
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS)
	rm -rf $(OBJ_DIR_BONUS)	

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all

valgrind: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all ./pipex fil.txt "cat" "ls" file2.txt

.PHONY:	all clean fclean re valgrind bonus