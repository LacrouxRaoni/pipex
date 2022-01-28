# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 16:17:34 by rruiz-la          #+#    #+#              #
#    Updated: 2022/01/27 23:53:53 by rruiz-la         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
NAME_BONUS	=	pipex_bonus

PATH_LIBFT	=	./lib/libft
LIBFT	=	$(PATH_LIBFT)/libft.a

I_PIPEX	=	-I ./include

I_LIBFT	=	-I ./ -I ./lib/libft/
LINK	=	-I ./ -I ./lib/libft/ -L./lib/libft/ -lft


CC	=	clang
CFLAGS	=	-Wall -Wextra -Werror -g

LIB_DIR	=	LIB

SRC_DIR	=	src
SRC_FILES	=	pipex.c \
				cmd_setup.c \
				split_pipex.c \
				free_pipex.c \

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC_DIR_BONUS	=	src_bonus
SRC_FILES_BONUS	=	main_bonus.c \
					pipex_bonus.c \
					cmd_setup_bonus.c \
					split_pipex_bonus.c \
					free_pipex_bonus.c \
					here_doc_bonus.c

SRC_BONUS	=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJ_DIR = obj
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR_BONUS = obj_bonus
OBJ_BONUS	=	$(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

HEADER	=	pipex.h
HEADER	=	pipex_bonus.h

FS	=	-fsanitize=address -g3

all:	$(NAME)

bonus: $(NAME_BONUS)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(FS) $(OBJ) $(LINK) -o $(NAME) $(I_PIPEX)

$(NAME_BONUS):	$(LIBFT) $(OBJ_DIR_BONUS) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LINK) -o $(NAME_BONUS) $(I_PIPEX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(OBJ_DIR):
	mkdir obj

$(OBJ_DIR_BONUS):
	mkdir obj_bonus

clean: 
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS)
	rm -rf $(OBJ_DIR_BONUS)	
	rm file2.txt
	make -C $(PATH_LIBFT) clean

fclean:
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	make -C $(PATH_LIBFT) clean	

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex file1.txt "catza" "wc -l" file2.txt

.PHONY:	all clean fclean re valgrind bonus