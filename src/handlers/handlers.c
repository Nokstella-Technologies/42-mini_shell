/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:58:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/18 17:41:50 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int verify_pipe(t_ms *ms, t_bool is_on_while, int *a)
{
	exec_command(ms->cmd[ms->cmd_file_now], ms);
	ms->cmd_file_now = *a + 1;
	ms->cmd_now++;
	*a++;
	if(is_on_while == TRUE)
		return (2);
	return (1);
}

static int verify_file(t_ms *ms, int type, t_bool is_on_while, int *a)
{
	if(type == 0)
	{
		custom_close(&ms->fd.in_fd);
		ms->fd.in_fd = open(ms->cmd[ms->cmd_file_now + 1]->line_cmd, O_RDONLY);
	}
	else if (type == 1)
		ms->fd.tmp_out = open(ms->cmd[ms->cmd_file_now + 1]->line_cmd, O_RDWR |O_CREAT, 0644);
	else if (type == 2)
		ms->fd.tmp_out = open(ms->cmd[ms->cmd_file_now + 1]->line_cmd, O_RDWR |O_CREAT | O_TRUNC, 0644);
	if (ms->fd.tmp_out == -1 || ms->fd.in_fd == -1)
	{
		dup_custom(ms->fd_origin[1], STDOUT_FILENO);
		printf("minishell: %s\n", strerror(errno));
		custom_close(&ms->fd.fd[0]);
		custom_close(&ms->fd.fd[1]);
	}
	*a++;
	if(is_on_while == TRUE)
		return (3);
	return(2);
}

static int verify_heredoc(t_ms *ms, t_bool is_on_while, int *a)
{
	heredoc(ms, ms->cmd[ms->cmd_file_now +1]);
	custom_close(&ms->fd.in_fd);
	ms->fd.in_fd = ms->fd.heredoc_fd;
	*a++;
	if(is_on_while == TRUE)
		return (3);
	return (2);
}


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
				i += verify_file(ms, 0, TRUE, &a);
			else if (ms->handlers[i + 1] == '>')
				i += verify_file(ms, 1, TRUE, &a);
			else if (ms->handlers[i + 1] == 't')
				i += verify_file(ms, 2, TRUE, &a);
			else if (ms->handlers[i + 1] == 'p')
				i += verify_pipe(ms, TRUE, &a);
			else if (ms->handlers[i + 1] == 'h')
				i += verify_heredoc(ms, TRUE, &a);
			else
				i += verify_pipe(ms, FALSE, &a);
		}
		else if (ms->handlers[i] == '<')
			i += verify_file(ms, 0, FALSE, &a);
		else if (ms->handlers[i + 1] == '>')
			i += verify_file(ms, 1, FALSE, &a);
		else if (ms->handlers[i] == 't')
			i += verify_file(ms, 2, FALSE, &a);
		else if (ms->handlers[i] == 'p')
			i += verify_pipe(ms, FALSE, &a);
	}
	if(ms->cmd_now != ms->cmd_number)
		exec_command(ms->cmd[ms->cmd_file_now], ms);
}