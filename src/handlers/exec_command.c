/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:05:33 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/09 16:00:54 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	change_pipe_final(t_exec *exec)
{
	if (exec->ms->fd.tmp_out != 0)
	{
		custom_close(&exec->ms->fd.fd[1]);
		exec->ms->fd.fd[1] = exec->ms->fd.tmp_out;
	}
	else if (exec->ms->cmd_number == exec->ms->cmd_now + 1)
	{
		custom_close(&exec->ms->fd.fd[1]);
		if (exec->ms->fd.out_fd != 1)
			exec->ms->fd.fd[1] = exec->ms->fd.out_fd;
		else
			exec->ms->fd.fd[1] = dup(exec->ms->fd_origin[1]);
	}
}

static void	pipe_change_exc(t_cmd *cmd, t_fds *fd, int fd_tmp, t_exec *exec)
{
	pid_t	pid;

	change_pipe_final(exec);
	if (exec->builtins == FALSE)
	{
		pid = fork();
		if (pid == -1)
			custom_perror(exec->ms, errno, strerror(errno));
		else if (pid == 0)
			pipe_exit(cmd, fd, fd_tmp, exec);
		wait4(pid, exec->ms->err, WNOHANG, NULL);
	}
	else
	{
		dup_custom(fd_tmp, STDIN_FILENO);
		dup_custom(fd->fd[1], STDOUT_FILENO);
		exec->command(exec->ms);
	}
	if (exec->ms->fd.in_fd == exec->ms->fd.heredoc_fd)
	{
		if (unlink("./.tmp") != 0)
			custom_perror(exec->ms, errno, strerror(errno));
	}
	if (exec->ms->fd.tmp_out != 0)
	{
		fd->in_fd = fd->tmp_out;
		fd->tmp_out = 0;
	}
	else
	{
		if (fd->in_fd != 0)
			custom_close(&fd->in_fd);
		fd->in_fd = fd->fd[0];
		custom_close(&fd->fd[1]);
	}
 }

static void	pcc(void (*commands)(t_ms *), t_exec *exec, t_ms *ms)
{
	exec->ms = ms;
	exec->command = commands;
	exec->builtins = TRUE;
}

static int	testing_our_commands(t_cmd *cmd, t_exec *exec, t_ms *ms)
{
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		pcc(&command_cd, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		pcc(&command_echo, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		pcc(&command_env, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		pcc(&command_exit, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		pcc(&command_export, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		pcc(&command_pwd, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		pcc(&command_unset, exec, ms);
	else if (ft_strncmp(cmd->argv[0], "history", 8) == 0)
		pcc(&command_history, exec, ms);
	else
		return (1);
	return (0);
}

void	exec_command(t_cmd *cmd, t_ms *ms)
{
	t_exec	exec;
	char	*tmp;
	int		a;

	exec.ms = ms;
	exec.builtins = FALSE;
	if (cmd == NULL || cmd->line_cmd == NULL)
		return ;
	cmd->argv = ft_split_pipe(cmd->line_cmd);
	a = 0;
	while(cmd->argv[a] != NULL)
	{
		tmp = verify_quotes(cmd->argv[a], 0);
		free_ptr((void **)&cmd->argv[a]);
		cmd->argv[a] = tmp;
		a++;
	}
	tmp = verify_quotes(cmd->line_cmd, 0);
	free_ptr((void **)&cmd->line_cmd);
	cmd->line_cmd = tmp;
	exec_elf(cmd);
	testing_our_commands(cmd, &exec, ms);
	pipe_change_exc(cmd, &ms->fd, ms->fd.in_fd, &exec);
}
