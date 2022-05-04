/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/12 21:20:39 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	testing_programing(t_cmd **cmd, int a)
{
	if (find_cmd(cmd[a]) != 0)
		return (127);
	// if (verify_custom_commands(cmd[a], cmd[a]->argv[0]))
	// 	return (127);
	else if (testing_access(cmd[a]) != 0)
		return (127);
	return (0);
}

static void	pipe_change(t_cmd **cmd, t_fds *fd, int a, int fd_tmp)
{
	close(fd->fd[0]);
	if (dup_custom(fd_tmp, STDIN_FILENO, cmd[a]) == - 1)
		exit(37);
	if (cmd[a + 1] == NULL)
		dup_custom(fd->out_fd, STDOUT_FILENO, cmd[a]);
	else
		dup_custom(fd->fd[1], STDOUT_FILENO, cmd[a]);
	if (execve(cmd[a]->path_cmd, cmd[a]->argv, g_envp) == -1)
		printf("error execve\n");
}

static int	execute_cmds(t_cmd **cmd, t_fds *fd, int a, int fd_tmp)
{
	pid_t	pid;
	int		test;
	
	pid = fork();
	if (pid == -1)
		printf("error to try fork");
	else if (pid == 0)
	{
		if (testing_programing(cmd, a) != 0)
			command_not_found(cmd[a]);
		else
			pipe_change(cmd, fd, a, fd_tmp);
		exit (0);
	}
	wait(&test);
	close(fd->in_fd);
	fd->in_fd = fd->fd[0];
	close(fd->fd[1]);
	return (0);
}


void	ms_pipe(t_cmd **cmds, t_fds *fds)
{
	int	i;
	
	i = 0;
	while(cmds[i] != NULL)
	{
		if (pipe(fds->fd) == -1)
			printf("error pipe 1\n");
		else if (execute_cmds(cmds, fds, i, fds->in_fd) == -1)
			printf("error pipe 2\n");
		i++;
	}
}