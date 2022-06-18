#include "tests.h"

char g_read[2048];

char **g_envp;
 
static char **	create_envp(char **envp)
{
	char	**tmp;
	int		a;

	a = 0;
	while(envp[a] != NULL)
		a++;
	tmp = (char **)malloc((a + 1)* sizeof(char *));
	a = 0;
	while(envp[a] != NULL)
	{
		tmp[a] = ft_strdup(envp[a]);
		a++;
	}
	tmp[a] = NULL;
	return(tmp);
}

int main(int argc, char **argv, char **envp) {
  g_envp = create_envp(envp);
  int i = 0;

  getcwd(g_read, 1024);
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
}
