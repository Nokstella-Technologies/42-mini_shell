// #include "tests.h"
// #include <string.h>
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wwrite-strings"


// // TEST(SPLIT_PIPE_1, test_parse_before_exec_ls) {
// // 	t_cmd	*cmd;

// // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // 	cmd->line_cmd = ft_strdup("ls -l");
// // 	cmd->argv = ft_split_pipe(cmd->line_cmd);
// // 	EXPECT_STREQ(cmd->argv[0], "ls");
// // 	EXPECT_STREQ(cmd->argv[1], "-l");
// // }

// // TEST(SPLIT_PIPE_2, test_parse_before_exec_hard_quotes) {
// // 	t_cmd	*cmd;

// // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // 	cmd->line_cmd = ft_strdup("tr '|' '&'");
// // 	cmd->argv = ft_split_pipe(cmd->line_cmd);
// // 	EXPECT_STREQ(cmd->argv[0], "tr");
// // 	EXPECT_STREQ(cmd->argv[1], "'|'");
// // 	EXPECT_STREQ(cmd->argv[2], "'&'");
// // }


// // TEST(SPLIT_PIPE_3, test_parse_before_exec_hard_quotes_second) {
// // 	t_cmd	*cmd;

// // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // 	cmd->line_cmd = ft_strdup("xargs echo \"obase=13;ibase=5;\"");
// // 	cmd->argv = ft_split_pipe(cmd->line_cmd);
// // 	EXPECT_STREQ(cmd->argv[0], "xargs");
// // 	EXPECT_STREQ(cmd->argv[1], "echo");
// // 	EXPECT_STREQ(cmd->argv[2], "\"obase=13;ibase=5;\"");
// // }

// // TEST(SPLIT_PIPE_4, test_simple_for_exec_ls) {
// // 	t_cmd	*cmd;

// // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // 	cmd->line_cmd = ft_strdup("tr \"'\\\"?!\" \"01234\"");
// // 	cmd->argv = ft_split_pipe(cmd->line_cmd);
// // 	EXPECT_STREQ(cmd->argv[0], "tr");
// // 	EXPECT_STREQ(cmd->argv[1], "\"'\\\"?!\"");
// // 	EXPECT_STREQ(cmd->argv[2], "\"01234\"");
// // }

// // TEST(SPLIT_PIPE_5, test_cd_only) {
// // 	t_cmd	*cmd;

// // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // 	cmd->line_cmd = ft_strdup("cd");
// // 	cmd->argv = ft_split_pipe("cd");
// // 	EXPECT_STREQ(cmd->argv[0], "cd");
// // }

// // // TEST(EXEC_CD, test_cd_unitest) {
// // // 	t_ms	*ms;
// // // 	t_cmd	*cmd;
// // // 	char res[400];
// // // 	char *env = getenv("PWD");

// // // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // // 	ms = (t_ms *)malloc(1 * sizeof(t_ms));
// // // 	cmd->line_cmd = ft_strdup("cd /home/luiz/42/welton");
// // // 	ms->fd.in_fd = 1;
// // // 	ms->fd.out_fd = 0;
// // // 	pipe(ms->fd.fd);
// // // 	exec_command(cmd, ms);
// // // 	getcwd(res, 400);
// // // 	EXPECT_STREQ(res, "/home/luiz/42/welton");
// // // 	EXPECT_STREQ(getenv("PWD"), "/home/luiz/42/welton");
// // // 	EXPECT_STREQ(getenv("OLDPWD"), env);
// // // 	chdir(getenv("OLDPWD"));
// // // 	free(cmd->argv[0]);
// // // 	free(cmd->argv[1]);
// // // 	free(cmd->argv);
// // // 	free(cmd->line_cmd);
// // // 	free(cmd);
// // // 	free(ms);
// // // }

// // // TEST(EXEC_CD_1, test_cd_unitest_root_shortcut) {
// // // 	t_ms	*ms;
// // // 	t_cmd	*cmd;
// // // 	char res[400];
// // // 	char *env = getenv("PWD");
	

// // // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // // 	ms = (t_ms *)malloc(1 * sizeof(t_ms));
// // // 	cmd->line_cmd = ft_strdup("cd /");
// // // 	ms->fd.in_fd = 1;
// // // 	ms->fd.out_fd = 0;
// // // 	pipe(ms->fd.fd);
// // // 	exec_command(cmd, ms);
// // // 	getcwd(res, 400);
// // // 	EXPECT_STREQ(res, "/");
// // // 	EXPECT_STREQ(getenv("PWD"), "/");
// // // 	EXPECT_STREQ(getenv("OLDPWD"), env);
// // // 	chdir(getenv("OLDPWD"));
// // // 	free(cmd->argv[0]);
// // // 	free(cmd->argv);
// // // 	free(cmd->line_cmd);
// // // 	free(cmd);
// // // 	free(ms);
// // // }

// // TEST(EXEC_CD_2, test_cd_unitest_home_shortcut) {
// // 	t_ms	*ms;
// // 	t_cmd	*cmd;
// // 	char res[400];
// // 	char *env = getenv("PWD");
	

// // 	cmd = (t_cmd *)malloc(1 * sizeof(t_cmd));
// // 	ms = (t_ms *)malloc(1 * sizeof(t_ms));
// // 	cmd->line_cmd = ft_strdup("cd ~");
// // 	ms->fd.in_fd = 1;
// // 	ms->fd.out_fd = 0;
// // 	pipe(ms->fd.fd);
// // 	exec_command(cmd, ms);
// // 	getcwd(res, 400);
// // 	EXPECT_STREQ(res, "/home/luiz/");
// // 	EXPECT_STREQ(getenv("PWD"), "/home/luiz");
// // 	EXPECT_STREQ(getenv("OLDPWD"), env);
// // 	chdir(getenv("OLDPWD"));
// // 	free(cmd->argv[0]);
// // 	free(cmd->argv);
// // 	free(cmd->line_cmd);
// // 	free(cmd);
// // 	free(ms);
// // }





// #pragma GCC diagnostic pop