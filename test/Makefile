NAME = test
LIBFT = ../libft/others/*.c ../libft/bonus/*.c ../libft/src/*.c ../libft/others/printf/*.c

SRC = *.cpp
CMDS = ../src/commands/*.c
HAND = ../src/handlers/*.c
UTILS = ../src/utils/*.c

all: $(NAME)

$(NAME):
	g++ -I ../header  -I ../libft $(LIBFT) $(SRC) $(CMDS) $(HAND) $(UTILS) -lgtest_main -lgtest -lpthread  -o $(NAME) -fpermissive -Wwrite-strings -g3

run:
	./test

val:
	valgrind --leak-check=full ./test

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re run val
