/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:34 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/03 02:25:12 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int count_argv(t_cmd *cmd)
{
	int	a;

	a = 0;
	while (cmd->argv[a] != NULL)
		a++;
	return(a);
}

void	command_exit(t_ms *ms)
{
	int	exitS;

	exitS = 0;
	custom_close(&ms->fd.in_fd);
	ms->fd.in_fd = ms->fd.fd[0];
	custom_close(&ms->fd.fd[1]);
	if (count_argv(ms->cmd[ms->cmd_now]) > 2)
	{
		ft_putstr_fd(" too many arguments", STDERR_FILENO);
		exitS = 1;
	}
	else if (ms->cmd[ms->cmd_now]->argv[1] != NULL)
	{
			exitS = ft_atoi(ms->cmd[ms->cmd_now]->argv[1]);
	}
	free_g_envp();
	end_program(&ms);
	exit(exitS);
}
