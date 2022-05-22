#include "tests.h"
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

TEST(SPLIT_PARSE, teste_parse){
	char **str = ft_split_pipe("export LUIZ=Teste");

	EXPECT_STREQ(str[0], "export");
	EXPECT_STREQ(str[1], "LUIZ=Teste");
}
TEST(SPLIT_PARSE, teste_parse_quote_space_env_envvalue){
	char **str = ft_split_pipe("export LUIZ=Teste");

	EXPECT_STREQ(str[0], "export");
	EXPECT_STREQ(str[1], "LUIZ=Teste");
}
TEST(SPLIT_PARSE, teste_parse_space_env_envvalue_light){
	char **str = ft_split_pipe("export 'LUIZ=Teste'");

	EXPECT_STREQ(str[0], "export");
	EXPECT_STREQ(str[1], "'LUIZ=Teste'");
}
TEST(SPLIT_PARSE, teste_parse_space_env_envvalue_medium){
	char **str = ft_split_pipe("export \"LUIZ=Teste\"");

	EXPECT_STREQ(str[0], "export");
	EXPECT_STREQ(str[1], "\"LUIZ=Teste\"");
}
TEST(SPLIT_PARSE, teste_parse_space_env_envvalue_hard){
	char **str = ft_split_pipe("export \"LU\"'IZ'=\"Tes \"te");

	EXPECT_STREQ(str[0], "export");
	EXPECT_STREQ(str[1], "\"LU\"'IZ'=\"Tes \"te");
}



#pragma GCC diagnostic pop