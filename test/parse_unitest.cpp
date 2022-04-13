#include "tests.h"
#include <string.h>

TEST(PARSE, test_parse_unitest) {
	t_ms	*ms;

	ms = parse_string("ls -l");
	EXPECT_STREQ(ms->cmd[0]->line, "ls -l");
	
}

