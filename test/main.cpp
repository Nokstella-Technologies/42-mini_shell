#include "tests.h"

char g_read[2048];

char **g_envp;
 
int main(int argc, char **argv, char **envp) {
  g_envp = envp;

  getcwd(g_read, 1024);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}