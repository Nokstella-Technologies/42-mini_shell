/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an7onie77i <an7onie77i@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:58:20 by an7onie77i        #+#    #+#             */
/*   Updated: 2022/05/28 17:14:57 by an7onie77i       ###   ########.fr       */
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
				exec_command(ms->cmd[j], ms);
				i += 2;
			}
			else
			{
				exec_command(ms->cmd[j], ms);
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