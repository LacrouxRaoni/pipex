# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 16:17:34 by rruiz-la          #+#    #+#              #
#    Updated: 2022/01/12 13:04:58 by rruiz-la         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

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
				free_pipex.c

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADER	=	pipex.h

FS	=	-fsanitize=address -g3

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(FS) $(OBJ) $(LINK) -o $(NAME) $(I_PIPEX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(OBJ_DIR):
	mkdir obj

clean: 
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm file2.txt
	make -C $(PATH_LIBFT) clean

fclean:
	rm -rf $(NAME)
	make -C $(PATH_LIBFT) clean	

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex

.PHONY:	all clean fclean re valgrind