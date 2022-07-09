/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/09 15:35:54 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ms_pipe(t_cmd **cmds, t_fds *fds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
	{
		if (pipe(fds->fd) == -1)
			ft_printf("error pipe 1\n");
		i++;
	}
}
