#include "gtest/gtest.h"
#include "mini_shell.h"


TEST(PWD_unitest, test_pwd_unitest) {
	char res[1024];
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(fd[1], 1);
		close(fd[0]);
		pwd();
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	fgets(res, 1024, fdopen(fd[0], "r"));
	close(fd[0]);
	EXPECT_STREQ(res, "/home/luiz/42/minishell/test\n");
}

TEST(cd_unitest, test_move_to_pp)
{
	char	res[1024];

	cd("..")
	getcwd(res, 1024);
	EXPECT_STREQ(res, "/home/luiz/42/minishell");
}