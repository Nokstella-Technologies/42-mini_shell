/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:58:20 by an7onie77i        #+#    #+#             */
/*   Updated: 2022/06/12 16:45:48 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void verify_next_move(t_ms *ms)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (ms->handlers[i] != 0)
	{
		if (ms->handlers[i] == 'c')
		{ 
			if (pipe(ms->fd.fd))
				printf("error pipe\n");
			if (ms->handlers[i + 1] == 'p')
			{
				exec_command(ms->cmd[j], ms, j);
				i += 2;
			}
			else
			{
				exec_command(ms->cmd[j], ms, j);
				i++;
			}
			j++;
		}
		// else if (ms->handlers[i] == "c" && ms->handlers[i + 1] == "o")
		// {
		// 	ms_or(ms);
		// 	i +=
		// }
		
	}
}