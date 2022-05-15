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
	a = 0;
	tmp = (char **)malloc(a * sizeof(char *));
	while(envp[a] != NULL)
	{
		tmp[a] = ft_strdup(envp[a]);
		a++;
	}
	return(tmp);
}


int main(int argc, char **argv, char **envp) {
  g_envp = create_envp(envp);

  getcwd(g_read, 1024);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}