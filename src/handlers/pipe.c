/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:20 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/28 12:22:41 by vantonie         ###   ########.fr       */
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
			printf("error pipe 1\n");
		i++;
	}
}
