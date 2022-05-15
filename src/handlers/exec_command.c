/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:05:33 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/15 01:00:42 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// parse isso = cmd->cmd_line
// ou cria isso cmd->path_cmd e executa com exec
// ou executa o comando necessario dos recriados
// cmd->argv


static void	pipe_change_exc(t_cmd *cmd, t_fds *fd, int fd_tmp, int *err)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd->fd[0]);
		dup_custom(fd_tmp, STDIN_FILENO);
		dup_custom(fd->fd[1], STDOUT_FILENO);
		if (execve(cmd->path_cmd, cmd->argv, g_envp) == -1)
			printf("error execve\n");
		exit(0);
	}
	wait(err);
	close(fd->in_fd);
	fd->in_fd = fd->fd[0];
	close(fd->fd[1]);
}

static void	pipe_change_commands(void (*commands)(t_cmd *), t_cmd *cmd, t_fds *fds)
{
	dup_custom(fds->in_fd, STDIN_FILENO);
	dup_custom(fds->fd[1], STDOUT_FILENO);
	commands(cmd);
	close(fds->in_fd);
	fds->in_fd = fds->fd[0];
	close(fds->fd[1]);
}

static int	testing_our_commands(t_cmd *cmd, t_fds *fds)
{
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		pipe_change_commands(&command_cd, cmd, fds);
	else if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		pipe_change_commands(&command_echo, cmd, fds);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		pipe_change_commands(&command_env, cmd, fds);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		pipe_change_commands(&command_exit, cmd, fds);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		pipe_change_commands(&command_export, cmd, fds);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		pipe_change_commands(&command_pwd, cmd, fds);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		pipe_change_commands(&command_unset, cmd, fds);
	else
		return (1);
	return (0);
}

void	exec_command(t_cmd *cmd, t_ms *ms)
{
	if (cmd == NULL || cmd->line_cmd == NULL)
		return ;
	cmd->argv = ft_split_pipe(cmd->line_cmd);
	if (testing_our_commands(cmd, &ms->fd) == 0)
		return ;
	else if (testing_access(cmd) == 0)
		pipe_change_exc(cmd, &ms->fd, ms->fd.in_fd, &ms->err);
	else
		command_not_found(cmd);
}
