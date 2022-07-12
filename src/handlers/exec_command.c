/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:05:33 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/12 19:25:42 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	pipe_change_exc(t_cmd *cmd, t_fds *fd, t_exec *exec)
{
	pid_t	pid;

	ft_sigaction();
	pid = fork();
	if (pid == -1)
		custom_perror(exec->ms->err, errno, strerror(errno), "fork");
	else if (pid == 0)
	{
		if (testing_access(cmd) == 0)
		{
			custom_close(&fd->fd[0]);
			if (execve(cmd->path_cmd, cmd->argv, g_envp) == -1)
				custom_perror(exec->ms->err, errno, strerror(errno), "execve");
		}
		else
			exit(command_not_found(exec->ms, cmd->argv[0]));
		kill(pid, 256);
	}
	wait4(pid, exec->ms->err, 0, NULL);
	if (WIFEXITED(*exec->ms->err))
		*exec->ms->err = WEXITSTATUS(*exec->ms->err);
	else if (WIFSIGNALED(*exec->ms->err))
		*exec->ms->err = WTERMSIG(*exec->ms->err) + 128;
	pipe_exit(fd, exec);
}

static t_bool	pcc(void (*commands)(t_ms *), t_exec *exec, t_ms *ms)
{
	commands(ms);
	exec->builtins = TRUE;
	return (TRUE);
}

static t_bool	testing_our_commands(t_cmd *cmd, t_exec *exec, t_ms *ms)
{
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (pcc(&command_cd, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (pcc(&command_echo, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (pcc(&command_env, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (pcc(&command_exit, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (pcc(&command_export, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (pcc(&command_pwd, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (pcc(&command_unset, exec, ms));
	else if (ft_strncmp(cmd->argv[0], "history", 8) == 0)
		return (pcc(&command_history, exec, ms));
	else
		return (FALSE);
}

t_ms	*fix_quotes(t_cmd *cmd, t_ms *ms)
{
	int		a;
	char	*tmp;

	if (cmd == NULL || cmd->line_cmd == NULL)
		return (ms);
	cmd->argv = ft_split_pipe(cmd->line_cmd);
	a = 0;
	while (cmd->argv[a] != NULL)
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
	return (ms);
}

void	exec_command(t_cmd *cmd, t_ms *ms)
{
	t_exec	exec;

	exec.ms = fix_quotes(cmd, ms);
	exec.builtins = FALSE;
	change_pipe_final(&exec, exec.ms->fd.in_fd);
	if (testing_our_commands(cmd, &exec, ms) == FALSE)
		pipe_change_exc(cmd, &ms->fd, &exec);
	else
		pipe_exit(&ms->fd, &exec);
}
