/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/09 23:34:31 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	pipe_exit(t_fds *fd, t_exec *exec)
{
	if (fd->in_fd == fd->heredoc_fd)
	{
		if (unlink("./.tmp") != 0)
			custom_perror(exec->ms, errno, strerror(errno));
		fd->heredoc_fd = -1;
	}
	if (exec->ms->fd.tmp_out != 0)
	{
		fd->in_fd = fd->tmp_out;
		fd->tmp_out = 0;
	}
	else
	{
		if (fd->in_fd != 0)
			custom_close(&fd->in_fd);
		fd->in_fd = fd->fd[0];
		custom_close(&fd->fd[1]);
	}
}

void	add_token(t_ms *ms, char *token)
{
	char	*tmp;

	tmp = ms->handlers;
	ms->handlers = ft_formatf("%s%s", ms->handlers, token);
	free(tmp);
}

char	*verify_token(t_ms *ms, char *s_tmp, char a)
{
	if (*s_tmp == a)
	{
		if (*s_tmp == '|')
			add_token(ms, "o");
		else if (*s_tmp == '>')
			add_token(ms, "t");
		else if (*s_tmp == '<')
			add_token(ms, "h");
		return (s_tmp + 1);
	}
	else if (*s_tmp == '|' || *s_tmp == '>' || *s_tmp == '<' || *s_tmp == '&')
		ms->err[0] = -2;
	if (a == '|')
		add_token(ms, "|");
	if (a == '>')
		add_token(ms, ">");
	if (a == '<')
		add_token(ms, "<");
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
			|| ms->handlers[strlen - 1] == 't'))
		add_token(ms, "f");
	else
	{
		ms->cmd_number ++;
		add_token(ms, "c");
	}
}
