NAME = test
LIBFT = ../libft/others/*.c ../libft/bonus/*.c ../libft/src/*.c ../libft/others/printf/*.c

SRC = *.cpp
CMDS = ../src/commands/*.c
HAND = ../src/handlers/*.c

all: $(NAME)

$(NAME):
	g++ -I ../header  -I ../libft $(LIBFT) $(SRC) $(CMDS) $(HAND) -lgtest_main -lgtest -lpthread -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
	