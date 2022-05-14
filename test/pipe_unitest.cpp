#include "tests.h"
#include <string.h>

// TEST(PIPE, test_pipe_unitest) {
// 	char res[2048];
// 	t_cmd **cmd;
// 	cmd = (t_cmd **)malloc(sizeof(t_cmd *) * 3);
// 	cmd[0]->line_cmd = strdup("ls -l");
// 	cmd[1]->line_cmd = strdup("grep main");
// 	cmd[2] = NULL;
// 	t_fds fds;
// 	fds.in_fd = 0;
// 	fds.out_fd = 1;

// 	ms_pipe(cmd, &fds);
// 	fgets(res, 2048, fdopen(fds.fd[1], "r"));
// 	EXPECT_STREQ(res, "-rw-r--r-- 1 luiz luiz 167 Apr  7 10:33 main.cpp");
// }
