#include "tests.h"
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

TEST(PARSE_1, test_parse_unitest_basic) {
	t_ms	*ms;

	ms = init_struct("ls -l");
	parse_string(ms, "ls -l", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls -l");
	EXPECT_STREQ(ms->handlers, "c");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_2, test_parse_unitest_with_pipe) {
	t_ms	*ms;

	ms = init_struct("ls -l | grep 'a'");
	parse_string(ms, "ls -l | grep 'a'", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls -l");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "grep 'a'");
	EXPECT_STREQ(ms->handlers, "cpc");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_3, test_parse_unitest_with_pipe_and_OR) {
	t_ms	*ms;

	ms = init_struct("ls -l|grep 'a'||tr 'a' 'o'");
	parse_string(ms, "ls -l|grep 'a'||tr 'a' 'o'", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls -l");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "grep 'a'");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "tr 'a' 'o'");
	EXPECT_STREQ(ms->handlers, "cpcoc");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_4, test_parse_unitest_with_pipe_and__OR_____) {
	t_ms	*ms;

	ms = init_struct("ls -l|grep 'a'    ||   tr 'a' 'o'");
	parse_string(ms, "ls -l|grep 'a'    ||   tr 'a' 'o'", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls -l");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "grep 'a'");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "tr 'a' 'o'");
	EXPECT_STREQ(ms->handlers, "cpcoc");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_5, test_parse_error_space_after_pipe_then_pipe) {
	t_ms	*ms;

	ms = init_struct("ls -l| |grep 'a'    ||   tr 'a' 'o'");
	parse_string(ms, "ls -l| |grep 'a'    ||     tr 'a' 'o'", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls -l");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "grep 'a'");
	EXPECT_STREQ(ms->cmd[3]->line_cmd, "tr 'a' 'o'");
	EXPECT_STREQ(ms->handlers, "cppcoc");
	EXPECT_EQ(ms->err, -2);
}

TEST(PARSE_6, test_parse_success_ls_out_file_or_comand) {
	t_ms	*ms;

	ms = init_struct("ls -l > out  ||   tr 'a' 'o'");
	parse_string(ms, "ls -l > out    ||     tr 'a' 'o'", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls -l");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "out");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "tr 'a' 'o'");
	EXPECT_STREQ(ms->handlers, "c>foc");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_7, test_parse_success_ls_out_file_or_comand) {
	t_ms	*ms;

	ms = init_struct("> out  ||   tr 'a' 'o'");
	parse_string(ms, "> out    ||     tr 'a' 'o'", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "out");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "tr 'a' 'o'");
	EXPECT_STREQ(ms->handlers, ">foc");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_8, test_parse_heredoc_start_with_out) {
	t_ms	*ms;

	ms = init_struct("<< out > line");
	parse_string(ms, "<< out > line", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "out");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "line");
	EXPECT_STREQ(ms->handlers, "hc>f");
	EXPECT_EQ(ms->err, 0);
}

TEST(PARSE_9, test_parse_unexpect_newline) {
	t_ms	*ms;

	ms = init_struct("ls >");
	parse_string(ms, "ls >", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls");
	EXPECT_STREQ(ms->handlers, "c>");
	EXPECT_EQ(ms->err, -2);
}

TEST(PARSE_10, test_parse_pipe_in_the_beggining) {
	t_ms	*ms;

	ms = init_struct("| ls");
	parse_string(ms, "| ls", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "ls");
	EXPECT_STREQ(ms->handlers, "pc");
	EXPECT_EQ(ms->err, -2);
}


TEST(PARSE_11, test_parse_or_in_the_beggining) {
	t_ms	*ms;

	ms = init_struct("|| ls");
	parse_string(ms, "|| ls", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "ls");
	EXPECT_STREQ(ms->handlers, "oc");
	EXPECT_EQ(ms->err, -2);
}

TEST(PARSE_12, test_parse_or_in_the_beggining) {
	t_ms	*ms;

	ms = init_struct("ls || | ls");
	parse_string(ms, "ls || | ls", 0, NULL);
	EXPECT_STREQ(ms->cmd[0]->line_cmd, "ls");
	EXPECT_STREQ(ms->cmd[1]->line_cmd, "");
	EXPECT_STREQ(ms->cmd[2]->line_cmd, "ls");
	EXPECT_STREQ(ms->handlers, "copc");
	EXPECT_EQ(ms->err, -2);
}


#pragma GCC diagnostic pop