/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/28 11:26:43 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	pipe_exit(t_fds *fd, t_ms *ms)
{
	if (fd->in_fd == fd->heredoc_fd)
	{
		if (unlink("./.tmp") != 0)
			custom_perror(ms->err, errno,
				"not possible to delete tmp file", ".tmp");
		fd->heredoc_fd = -1;
	}
	if (ms->fd.tmp_out != -1)
	{
		fd->in_fd = fd->tmp_out;
		fd->tmp_out = -1;
	}
	else
	{
		if (fd->in_fd != 0)
			custom_close(&fd->in_fd);
		fd->in_fd = fd->fd[0];
		custom_close(&fd->fd[1]);
	}
}

void	add_token(t_ms *ms, char token)
{
	char	*tmp;

	tmp = ms->handlers;
	ms->handlers = ft_formatf("%s%c", ms->handlers, token);
	free_ptr((void **) &tmp);
}

char	*verify_token(t_ms *ms, char *s_tmp, char a)
{
	if (*s_tmp == a && a != '|')
	{
		if (*s_tmp == '>')
			add_token(ms, 't');
		else if (*s_tmp == '<')
			add_token(ms, 'h');
		return (s_tmp + 1);
	}
	else if (*s_tmp == '|' || *s_tmp == '>' || *s_tmp == '<')
	{
		ms->err[0] = -2;
		add_token(ms, a);
	}
	if (a == '|')
		add_token(ms, '|');
	if (a == '>')
		add_token(ms, '>');
	if (a == '<')
		add_token(ms, '<');
	return (s_tmp);
}

int	verify_error(char *handlers, int len, int err)
{
	if (handlers[len - 1] != 'c' && handlers[len - 1] != 'f' && err == 0)
	{
		if (handlers[len - 1] == '|'
			|| handlers[len - 1] == 'a' || handlers[len - 1] == 'o' )
			return (1);
		return (-2);
	}
	return (err);
}

void	verify_cmd(t_ms *ms, char *str)
{
	int	strlen;

	strlen = ft_strlen(ms->handlers);
	if (*str == 0)
		return ;
	else if (strlen > 0 && (ms->handlers[strlen - 1] == '>'
			|| ms->handlers[strlen - 1] == '<'
			|| ms->handlers[strlen - 1] == 't'
			|| ms->handlers[strlen - 1] == 'h'))
	{
		ms->cmd_number ++;
		add_token(ms, 'f');
	}
	else
	{
		ms->cmd_number ++;
		add_token(ms, 'c');
	}
}
