/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:34 by vantonie          #+#    #+#             */
/*   Updated: 2022/08/02 12:19:39 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	verify_exit_error(char *str, t_ms *ms)
{
	int	a;

	a = 0;
	if (ms->cmd[ms->cmd_now]->argv[2] != NULL)
	{
		custom_perror(&ms->err_tmp, 1, " too many arguments", "exit");
		return (1);
	}
	while ((ft_isdigit(str[a]) || str[a] == '+' || str[a] == '-'
			|| str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		&& str[a] != 0)
		a++;
	if (str[a] != 0)
	{
		custom_perror(&ms->err_tmp, 2, " numeric argument required", "exit");
		return (2);
	}
	return (0);
}

void	command_exit(t_ms *ms)
{
	int	exit_s;

	exit_s = 0;
	custom_close(&ms->fd.fd[0]);
	custom_close(&ms->fd.fd[1]);
	if (ms->cmd[ms->cmd_now]->argv[1] != NULL)
	{
		exit_s = verify_exit_error(ms->cmd[ms->cmd_now]->argv[1], ms);
		if (exit_s == 0 && ms->cmd[ms->cmd_now]->argv[1] != NULL)
			exit_s = ft_atoi(ms->cmd[ms->cmd_now]->argv[1]);
	}
	ft_putstr_fd("exit\n", 2);
	free_g_envp();
	end_program(&ms);
	exit(exit_s);
}
