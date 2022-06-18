#include "tests.h"
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

TEST(free_all, test_format_env) {
	t_ms *ms;
	char *str = ft_strdup("pwd");

	ms = init_struct(str);
	tokeneer(ms, str, 0, NULL);
	pipe(ms->fd.fd);
	exec_command(ms->cmd[0], ms);
	end_program(&ms);
	EXPECT_TRUE(ms == NULL);
}

#pragma GCC diagnostic pop