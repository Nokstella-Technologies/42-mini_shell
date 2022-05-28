#include "tests.h"
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

TEST(SUB_ENV, test_format_env) {
	char *test;

	test = sub_env(NULL, ft_strdup("$SHELL"));
	EXPECT_STREQ(test, "/bin/zsh");
	free(test);
}

TEST(SUB_ENV, test_format_space_env) {
	char *test;

	test = sub_env(NULL, ft_strdup("$SHELL"));
	EXPECT_STREQ(test, "/bin/zsh");
	free(test);
}

TEST(SUB_ENV, test_format_space_env_text) {
	char *test;

	test = sub_env(NULL, ft_strdup("$SHELL asd"));
	EXPECT_STREQ(test, "/bin/zsh asd");
	free(test);
}

TEST(SUB_ENV, test_format_space_env_space_text) {
	char *test;

	test = sub_env(NULL, ft_strdup("$SHELL     asd"));
	EXPECT_STREQ(test, "/bin/zsh     asd");
	free(test);
}

TEST(SUB_ENV, test_format_subEnv__shell__shell__asd) {
	char *test;

	
	test = sub_env(NULL, ft_strdup("$SHELL  $SHELL  asd"));
	EXPECT_STREQ(test, "/bin/zsh  /bin/zsh  asd");
	free(test);
}

TEST(SUB_ENV, test_format_subEnv_shellshell) {
	char *test;

	test = sub_env(NULL, ft_strdup("$SHELL$SHELL"));
	EXPECT_STREQ(test, "/bin/zsh/bin/zsh");
		free(test);
}

TEST(SUB_ENV, test_format_subEnv_shellshel) {
	char *test;

	test = sub_env(NULL, ft_strdup("$SHELL$SHEL"));
	EXPECT_STREQ(test, "/bin/zsh");
		free(test);
}

#pragma GCC diagnostic pop