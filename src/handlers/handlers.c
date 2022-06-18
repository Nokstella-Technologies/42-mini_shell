/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:58:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/18 02:07:20 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// static int verify_next_move_exec_command(t_ms *ms, int a)
// {
// 	exec_command(ms->cmd[ms->cmd_file_now], ms);
// 	ms->cmd_file_now = a + 1;
// 	ms->cmd_now++;
// }

void verify_next_move(t_ms *ms)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while (ms->handlers[i] != 0)
	{
		if (ms->handlers[i] == 'c')
		{ 
			if (pipe(ms->fd.fd))
				printf("error pipe\n");
			if (ms->handlers[i + 1] == '<')
			{
				custom_close(&ms->fd.in_fd);
				ms->fd.in_fd = open(ms->cmd[ms->cmd_file_now + 1]->line_cmd, O_RDONLY);
				if (ms->fd.in_fd == -1)
				{
					dup_custom(ms->fd_origin[1], STDOUT_FILENO);
					printf("minishell: %s\n", strerror(errno));
					custom_close(&ms->fd.fd[0]);
					custom_close(&ms->fd.fd[1]);
					break;
				}
				i += 3;
				a++;
			}
			else if (ms->handlers[i + 1] == '>')
			{
				ms->fd.tmp_out = open(ms->cmd[ms->cmd_file_now + 1]->line_cmd, O_RDONLY | O_CREAT, 0644);
				if (ms->fd.in_fd == -1)
				{
					dup_custom(ms->fd_origin[1], STDOUT_FILENO);
					printf("minishell: %s\n", strerror(errno));
					custom_close(&ms->fd.fd[0]);
					custom_close(&ms->fd.fd[1]);
					break;
				}
				i += 3;
				a++;
			}
			else if (ms->handlers[i + 1] == 'p'){
				exec_command(ms->cmd[ms->cmd_file_now], ms);
				ms->cmd_file_now = a +1;
				ms->cmd_now++;
				i += 2;
				a++;
			}
			else
			{
				exec_command(ms->cmd[ms->cmd_file_now], ms);
				ms->cmd_file_now = a + 1;
				ms->cmd_now++;
				i++;
				a++;
			}
		}
		else if (ms->handlers[i] == 'p') {
			exec_command(ms->cmd[ms->cmd_file_now], ms);
			ms->cmd_file_now = a + 1;
			ms->cmd_now++;
			i++;
			a++;
		}
	}
	if(ms->cmd_now != ms->cmd_number)
		exec_command(ms->cmd[ms->cmd_file_now], ms);
}