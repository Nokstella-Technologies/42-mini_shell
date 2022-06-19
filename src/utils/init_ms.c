/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:32:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/06/18 21:03:19 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

t_ms *init_struct(char *line)
{
	t_ms *ms;

	ms = (t_ms *)malloc(sizeof(t_ms));
	ms->cmd = NULL;
	ms->line = ft_strdup(line);
	ms->fd.in_fd = 0;
	ms->fd.out_fd = 1;
	ms->fd.tmp_out = 0;
	ms->handlers = ft_strdup("");
	ms->err = 0;
	ms->cmd_number = 0;
	ms->fd_origin[0] = dup(STDIN_FILENO);
	ms->fd_origin[1] = dup(STDOUT_FILENO);
	ms->cmd_now = 0;
	ms->cmd_file_now = 0;
	ms->handlers_counter = 0;
	return(ms);
}
