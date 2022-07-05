/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:05:33 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/05 19:40:52 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	change_pipe_final(t_ms *ms)
{
	if (ms->fd.tmp_out != 0)
	{
		custom_close(&ms->fd.fd[1]);
		ms->fd.fd[1] = ms->fd.tmp_out;
	}
	else if (ms->cmd_number == ms->cmd_now + 1)
	{
		custom_close(&ms->fd.fd[1]);
		ms->fd.fd[1] = ms->fd.out_fd;
	}
}

static void	pipe_change_exc(t_cmd *cmd, t_fds *fd, int fd_tmp, t_ms *ms)
{
	pid_t	pid;

	change_pipe_final(ms);
	pid = fork();
	if (pid == -1)
		custom_perror(ms, errno, strerror(errno));
	else if (pid == 0)
		pipe_exit(cmd, fd, fd_tmp, ms);
	wait(ms->err);
	if (ms->err[0])
		custom_perror(ms, errno, strerror(errno));
	custom_close(&fd->in_fd);
	if (ms->fd.in_fd == ms->fd.heredoc_fd)
	{
		if (unlink("./.tmp") != 0)
			custom_perror(ms, errno, strerror(errno));
	}
	if (ms->fd.tmp_out != 0)
	{
		fd->in_fd = fd->tmp_out;
		fd->tmp_out = 0;
	}
	else
	{
		fd->in_fd = fd->fd[0];
		custom_close(&fd->fd[1]);
	}
}

static void	pcc(void (*commands)(void *), void **cmd, t_fds *fds, t_ms *ms)
{
	dup_custom(fds->in_fd, STDIN_FILENO);
	change_pipe_final(ms);
	dup_custom(fds->fd[1], STDOUT_FILENO);
	commands(*cmd);
	custom_close(&fds->in_fd);
	fds->in_fd = fds->fd[0];
	custom_close(&fds->fd[1]);
}

static int	testing_our_commands(t_cmd *cmd, t_fds *fds, t_ms *ms)
{
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		pcc((void (*)(void *)) & command_cd, (void **)&ms, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		pcc((void (*)(void *)) & command_echo, (void **)&ms, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		pcc((void (*)(void *)) & command_env, (void **)&cmd, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		pcc((void (*)(void *)) & command_exit, (void **)&ms, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		pcc((void (*)(void *)) & command_export, (void **)&ms, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		pcc((void (*)(void *)) & command_pwd, (void **)&cmd, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		pcc((void (*)(void *)) & command_unset, (void **) &cmd, fds, ms);
	else if (ft_strncmp(cmd->argv[0], "history", 8) == 0)
		pcc((void (*)(void *)) & command_history, (void **) &cmd, fds, ms);
	else
		return (1);
	return (0);
}

void	exec_command(t_cmd *cmd, t_ms *ms)
{
	char	*tmp;

	if (cmd == NULL || cmd->line_cmd == NULL)
		return ;
	tmp = verify_quotes(cmd->line_cmd, 0);
	free_ptr((void **)&cmd->line_cmd);
	cmd->line_cmd = tmp;
	exec_elf(cmd);
	cmd->argv = ft_strtok(cmd->line_cmd, ' ');
	if (testing_our_commands(cmd, &ms->fd, ms) == 0)
		return ;
	free_ptr((void **) &cmd->argv[0]);
	free_ptr((void **) &cmd->argv[1]);
	free_ptr((void **) &cmd->argv);
	cmd->argv = ft_split_pipe(cmd->line_cmd);
	if (testing_access(cmd) == 0)
		pipe_change_exc(cmd, &ms->fd, ms->fd.in_fd, ms);
	else
	{
		ms->err[0] = -1;
		command_not_found(cmd);
	}
}
