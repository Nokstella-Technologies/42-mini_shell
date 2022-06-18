/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/15 00:49:48 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// static int	execute_cmds(t_cmd **cmd, t_fds *fd, int a, int fd_tmp)
// {
// 	pid_t	pid;
// 	int		test;
	
// 	pid = fork();
// 	if (pid == -1)
// 		printf("error to try fork");
// 	else if (pid == 0)
// 	{
// 		pipe_change(cmd, fd, a, fd_tmp);
// 		exit (0);
// 	}
// 	wait(&test);
// 	custom_close(&fd->in_fd);
// 	fd->in_fd = fd->fd[0];
// 	custom_close(&fd->fd[1]);
// 	return (0);
// }


void	ms_pipe(t_cmd **cmds, t_fds *fds)
{
	int	i;
	
	i = 0;
	while(cmds[i] != NULL)
	{
		if (pipe(fds->fd) == -1)
			printf("error pipe 1\n");
		// else if (execute_cmds(cmds, fds, i, fds->in_fd) == -1)
		// 	printf("error pipe 2\n");
		i++;
	}
}