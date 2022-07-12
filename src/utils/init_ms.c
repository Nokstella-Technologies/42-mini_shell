/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:32:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/12 19:08:39 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_ms	*init_struct(char *line, int *err)
{
	t_ms	*ms;

	ms = (t_ms *)malloc(sizeof(t_ms));
	ms->cmd = NULL;
	ms->line = ft_strdup(line);
	ms->fd.in_fd = 0;
	ms->fd.out_fd = 1;
	ms->fd.tmp_out = -1;
	ms->fd.fd[0] = 0;
	ms->fd.fd[1] = 0;
	ms->fd.heredoc_fd = -1;
	ms->handlers = ft_strdup("");
	ms->err = err;
	ms->cmd_number = 0;
	ms->fd_origin[0] = dup(STDIN_FILENO);
	ms->fd_origin[1] = dup(STDOUT_FILENO);
	ms->cmd_now = 0;
	ms->cmd_file_now = 0;
	ms->handlers_counter = 0;
	return (ms);
}
