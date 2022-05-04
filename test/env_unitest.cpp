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
	EXPECT_STREQ(res, "SHELL=/bin/bash\n");
	free(res);
	res = get_next_line(fd[0]);
	EXPECT_STREQ(res, "COLORTERM=truecolor\n");
	free(res);
	close(fd[0]);
}


TEST(ENV_2, test_env_out) {
	char *res;
	int file = open("./out", O_RDWR);
	int out = dup(1);
	dup2(file, 1);
	command_env();
	res = get_next_line(file);
	dup2(out, 1);
	EXPECT_STREQ(res, "SHELL=/bin/bash\n");
	free(res);
	res = get_next_line(file);
	EXPECT_STREQ(res, "COLORTERM=truecolor\n");
	free(res);
	close(file);
}


#pragma GCC diagnostic pop