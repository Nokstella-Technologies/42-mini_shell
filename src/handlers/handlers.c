/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:58:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/09 23:51:47 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	verify_pipe(t_ms *ms, int f)
{
	if(pipe(ms->fd.fd) == -1)
		custom_perror(ms, 2, " error to create the pipe");
	exec_command(ms->cmd[ms->cmd_file_now], ms);
	ms->cmd_file_now = f;
	ms->cmd_now += f;
}

static int	out_file(t_ms *ms, char type, t_bool was_out, int f)
{
	if (type == '>')
	{
		custom_close(&ms->fd.tmp_out);
		ms->fd.tmp_out = open(ms->cmd[ms->cmd_file_now + f]->line_cmd,
				O_RDWR | O_CREAT, 0644);
	}
	else if (type == 't')
	{
		custom_close(&ms->fd.tmp_out);
		if (was_out == FALSE)
			ms->fd.tmp_out = open(ms->cmd[ms->cmd_file_now + f]->line_cmd,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		else 
			ms->fd.tmp_out = open(ms->cmd[ms->cmd_file_now + f]->line_cmd,
				O_RDWR | O_CREAT, 0644);
	}
	if (ms->fd.tmp_out == -1 || ms->fd.in_fd == -1)
		custom_perror(ms, 2, "No such file or directory");
	return (2);
}

static int	in_file(t_ms *ms, int f)
{
	int	fd;

	fd = open(ms->cmd[ms->cmd_file_now + f]->line_cmd, O_RDONLY , 0644);
	if (fd == -1)
		custom_perror(ms, 2, " No such file or directory");
	else
	{
		custom_close(&ms->fd.in_fd);
		ms->fd.in_fd = fd;
	}
	return (2);
}

static int	ver_here(t_ms *ms, int f)
{
	ms->fd.heredoc_fd = open("./.tmp", O_RDWR | O_CREAT, 0644);
	heredoc(ms, ms->cmd[ms->cmd_file_now + f]);
	custom_close(&ms->fd.in_fd);
	ms->fd.in_fd = ms->fd.heredoc_fd;
	return (2);
}

int	verify_next_move_token(t_ms *ms, int h, t_bool was_out, int f)
{
	char	token;

	token =  ms->handlers[h];
	if (token == 'c')
	{
		f++;
		h = verify_next_move_token(ms, h + 1, was_out, f);
		verify_pipe(ms, f);
	}
	else if (token == 't')
		verify_next_move_token(ms, h + out_file(ms, token, was_out, f),
			was_out, f);
	else if (token == '<')
		verify_next_move_token(ms, h + in_file(ms, f), was_out, f);
	else if (token == '>')
		verify_next_move_token(ms, h + out_file(ms, token, was_out, f),
			was_out, f);
	else if (token == 'h')
		verify_next_move_token(ms, h + ver_here(ms, f), was_out, f);
	else if (token == '|')
		return(h + 1);
	return (h);
}

void	verify_next_move(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->cmd_number)
	{
		ms->handlers_counter = verify_next_move_token(ms, ms->handlers_counter ,
			 FALSE, 0);
		i = ms->cmd_now;
	}
}
