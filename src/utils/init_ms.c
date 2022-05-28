/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an7onie77i <an7onie77i@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:32:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/28 17:16:46 by an7onie77i       ###   ########.fr       */
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
	ms->handlers = ft_strdup("");
	ms->err = 0;
	ms->fd_origin[0] = dup(STDOUT_FILENO);
	ms->fd_origin[1] = dup(STDIN_FILENO);
	return(ms);
}
