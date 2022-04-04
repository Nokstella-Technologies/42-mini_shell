NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

FILES = main.c			\
		mini_shell.c	\

SRC=$(addprefix src/, $(FILES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(SRC) $(CFLAGS) -I ./header -L ./libft -lft -lreadline -g3 -o $(NAME)

$(LIBFT):
	make others -C ./libft

clean:
	rm -f $(LIBFT_OBJS) $(NAME) $(NAME_BONUS)
	make clean -C ./libft
	rm -rf minishell.dSYM

fclean:
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re