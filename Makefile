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
	$(CC) $(SRC) $(CFLAGS) -I ./header -I ./libft -L ./libft -lft -lreadline -o $(NAME)  -g3  -fsanitize=address
#  -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

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

test4: re
	cd minishell_tester && ./tester pipes 

test5: re
	cd minishell_tester && ./tester redirects 

test2: re
	cd minishell_tester && ./tester builtins

test3: re
	cd minishell_tester && ./tester syntax

err:
	echo -e ".\minishell\n$teste\necho \$?\nexit\n" | bash 2> /dev/null | sed -r "s:\x1B\[[0-9;]*[mK]::g" | grep -v "$PROMPT" | grep -v ^exit$ | tail -n 1
.PHONY: all clean fclean re test test2 test3 test4 test5


#cat ./test_files/infile_big | grep oi
#env | sort | grep -v SHLVL | grep -v ^_
#export | sort | grep -v SHLVL | grep -v "declare -x _" | grep -v "PS.="
#cat minishell.h | grep ");"$
#export GHOST=123 | env | grep GHOST
