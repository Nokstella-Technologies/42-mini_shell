#include "tests.h"
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

TEST(ENV_1, test_env) {
	char *res;
	int fd[2];
	int err;
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(fd[1], 1);
		close(fd[0]);
		command_env();
		close(fd[1]);
		exit(0);
	}
	wait(&err);
	close(fd[1]);
	res = get_next_line(fd[0]);
	EXPECT_STREQ(res, "VSCODE_GIT_ASKPASS_MAIN=/home/luiz/.vscode-server/bin/da15b6fd3ef856477bf6f4fb29ba1b7af717770d/extensions/git/dist/askpass-main.js\n");
	free(res);
	res = get_next_line(fd[0]);
	EXPECT_STREQ(res, "WSLENV=VSCODE_WSL_EXT_LOCATION/up:VSCODE_SERVER_TAR/up\n");
	free(res);
	close(fd[0]);
}


TEST(ENV_2, test_env_out) {
	char *res;
	int file = open("./out", O_RDWR);
	int out = dup(1);
	dup2(file, 1);
	command_env();
	dup2(out, 1);
	int file2 = open("./out", O_RDWR);
	res = get_next_line(file2);
	EXPECT_STREQ(res, "VSCODE_GIT_ASKPASS_MAIN=/home/luiz/.vscode-server/bin/da15b6fd3ef856477bf6f4fb29ba1b7af717770d/extensions/git/dist/askpass-main.js\n");
	free(res);
	res = get_next_line(file2);
	EXPECT_STREQ(res, "WSLENV=VSCODE_WSL_EXT_LOCATION/up:VSCODE_SERVER_TAR/up\n");
	int a = 2;
	while(res != NULL)
	{
		res = get_next_line(file2);
		a++;
	}
	EXPECT_EQ(a, 33);
	free(res);
	close(file);
	close(file2);
}


#pragma GCC diagnostic pop