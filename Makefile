NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SIGNALS = signals.c \

HANDLERS = *.c

COMMANDS = *.c

ERROS = custom_error.c 

FILES = main.c			\
		mini_shell.c	\
		$(addprefix signals/, $(SIGNALS))	\
		$(addprefix handlers/, $(HANDLERS))	\
		$(addprefix error/, $(ERROS))		\
		$(addprefix commands/, $(COMMANDS))

SRC=$(addprefix src/, $(FILES)) 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(SRC) $(CFLAGS) -I ./header -I ./libft -L ./libft -lft -lreadline -g3 -o $(NAME) 

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

test:
	make re -C test

.PHONY: all clean fclean re test