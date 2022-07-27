#include "mini_shell.h"

void	change_pipe_final(t_exec *exec, int fd_tmp)
{
	if (fd_tmp != 0)
		dup_custom(fd_tmp, STDIN_FILENO);
	if (exec->ms->fd.tmp_out != -1)
	{
		dup_custom(exec->ms->fd.tmp_out, STDOUT_FILENO);
		exec->ms->fd.tmp_out = -1;
	}
	else if (exec->ms->cmd_now + 1 == exec->ms->cmd_number)
		dup_custom(exec->ms->fd_origin[1], STDOUT_FILENO);
	else
		dup_custom(exec->ms->fd.fd[1], STDOUT_FILENO);
}
