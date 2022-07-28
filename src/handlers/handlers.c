/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:58:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/28 11:29:06 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	verify_pipe(t_ms *ms)
{
	if (*ms->err != 2)
	{
		if (pipe(ms->fd.fd) == -1)
			custom_perror(ms->err, 2, " error to create the pipe", "pipe");
		exec_command(ms->cmd[ms->cmd_now], ms);
	}
}

static int	out_file(t_ms *ms, char type, t_bool was_out, int *f)
{
	if (type == '>' && *ms->err != 2)
	{
		custom_close(&ms->fd.tmp_out);
		ms->fd.tmp_out = open(ms->cmd[ms->cmd_now + *f]->line_cmd,
				O_RDWR | O_CREAT, 0644);
	}
	else if (type == 't' && *ms->err == 0)
	{
		custom_close(&ms->fd.tmp_out);
		if (was_out == FALSE)
			ms->fd.tmp_out = open(ms->cmd[ms->cmd_now + *f]->line_cmd,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			ms->fd.tmp_out = open(ms->cmd[ms->cmd_now + *f]->line_cmd,
					O_RDWR | O_CREAT, 0644);
	}
	if (ms->fd.tmp_out == -1 && *ms->err != 2)
		custom_perror(ms->err, 2, "No such file or directory",
			ms->cmd[ms->cmd_now + *f]->line_cmd);
	*f = *f + 1;
	ms->cmd_file_now += 1;
	return (2);
}

static int	in_file(t_ms *ms, int *f)
{
	int	fd;

	if (*ms->err != 2)
	{
		fd = open(ms->cmd[ms->cmd_now + *f]->line_cmd, O_RDONLY, 0644);
		if (fd == -1)
		{
			*ms->err = 2;
			ms->tmp = ft_strdup(ms->cmd[ms->cmd_now + *f]->line_cmd);
		}
		else
		{
			custom_close(&ms->fd.in_fd);
			ms->fd.in_fd = fd;
		}
	}
	*f = *f + 1;
	ms->cmd_file_now += 1;
	return (2);
}

static int	ver_here(t_ms *ms, int *f)
{
	pid_t	pid;

	init_sigaction(ms->sa, SIG_IGN, SIGINT);
	custom_close(&ms->fd.in_fd);
	pid = fork();
	if (pid == -1)
		custom_perror(ms->err, errno, strerror(errno), "fork");
	else if (pid == 0)
	{
		dup_custom(dup(ms->fd_origin[0]), STDIN_FILENO);
		dup_custom(dup(ms->fd_origin[1]), STDOUT_FILENO);
		ms->fd.heredoc_fd = open("./.tmp", O_RDWR | O_CREAT, 0777);
		heredoc(ms, f);
		exit (130);
	}
	ft_waitpid(ms, pid);
	custom_close(&ms->fd.heredoc_fd);
	ms->fd.heredoc_fd = open("./.tmp", O_RDWR | O_CREAT, 0777);
	ms->fd.in_fd = ms->fd.heredoc_fd;
	*f = *f + 1;
	ms->cmd_file_now += 1;
	return (2);
}

int	verify_next_move_token(t_ms *ms, int h, t_bool was_out, int *f)
{
	char	token;

	token = ms->handlers[h];
	if (token == 'c')
	{
		*f = *f + 1;
		h = verify_next_move_token(ms, h + 1, was_out, f);
		verify_pipe(ms);
	}
	else if (token == 'h')
		h = verify_next_move_token(ms, h + ver_here(ms, f), was_out, f);
	else if (token == '>')
		h = verify_next_move_token(ms, h + out_file(ms, token, was_out, f),
				was_out, f);
	else if (token == 't')
		h = verify_next_move_token(ms, h + out_file(ms, token, was_out, f),
				was_out, f);
	else if (token == '<')
		h = verify_next_move_token(ms, h + in_file(ms, f), was_out, f);
	else if (token == '|')
		return (h + 1);
	return (h);
}

void	verify_next_move(t_ms *ms)
{
	int	i;
	int	f;

	i = 0;
	while (i < ms->cmd_number)
	{
		f = 0;
		ms->handlers_counter = verify_next_move_token(ms, ms->handlers_counter,
				FALSE, &f);
		if (*ms->err == 2 && ms->tmp != NULL)
		{
			custom_perror(ms->err, 2, "No such file or directory", ms->tmp);
			free_ptr((void **) &ms->tmp);
		}
		pipe_exit(&ms->fd, ms);
		ms->cmd_now += f;
		i = ms->cmd_now;
	}
}
