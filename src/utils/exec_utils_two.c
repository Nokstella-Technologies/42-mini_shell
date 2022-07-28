/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:25:10 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/28 11:25:11 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (exec->ms->cmd_now + exec->ms->cmd_file_now + 1
		== exec->ms->cmd_number || exec->ms->cmd_now + 1
		== exec->ms->cmd_number)
		dup_custom(exec->ms->fd_origin[1], STDOUT_FILENO);
	else
		dup_custom(exec->ms->fd.fd[1], STDOUT_FILENO);
}
