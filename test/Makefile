NAME = test

SRC = *.cpp
CMDS = ../src/commands/*.c

all:
	@g++ -I ../header $(SRC) $(CMDS)  -lgtest_main -lgtest -lpthread  -o $(NAME)
	./test