NAME	=	pipex

I_PIPEX	=	-I ./include

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

SRC_DIR	=	src
SRC_FILES	=	pipex.c \
				pipex_utils1.c \
				pipex_utils2.c \

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADER	=	pipex.h

FS	=	-fsanitize=address -g3

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(FS) $(OBJ) -o $(NAME) $(I_PIPEX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(OBJ_DIR):
	mkdir obj

clean: 
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm file2.txt

fclean:
	rm -rf $(NAME)
	

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex

.PHONY:	all clean fclean re valgrind