NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SIGNALS = signals.c \

HANDLERS = *.c

COMMANDS = *.c

UTILS = *.c

ERROS = custom_error.c

FILES = main.c			\
		mini_shell.c	\
		$(addprefix signals/, $(SIGNALS))	\
		$(addprefix handlers/, $(HANDLERS))	\
		$(addprefix error/, $(ERROS))		\
		$(addprefix commands/, $(COMMANDS))	\
		$(addprefix utils/, $(UTILS))

SRC=$(addprefix src/, $(FILES)) 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) 
	$(CC) $(SRC) $(CFLAGS) -I ./header -I ./libft -L ./libft -lft -lreadline -o $(NAME) -fsanitize=address -g3
# -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

$(LIBFT):
	make others -C ./libft

clean:
	rm -f $(LIBFT_OBJS) $(NAME) $(NAME_BONUS)
	make clean -C ./libft
	rm -rf minishell.dSYM

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

test:
	make re -C test
	make run -C test

val:
	make re -C test
	make val -C test

test2: re
	cd minishell_tester && ./tester syntax

.PHONY: all clean fclean re test
