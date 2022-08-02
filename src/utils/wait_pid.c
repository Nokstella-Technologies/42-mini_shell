/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:27:24 by llima-ce          #+#    #+#             */
/*   Updated: 2022/08/02 12:21:24 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_waitpid(t_ms *ms, int pid)
{
	wait4(pid, &ms->err_tmp, 0, NULL);
	if (WIFEXITED(ms->err_tmp))
	{
		ms->err_tmp = WEXITSTATUS(ms->err_tmp);
	}
	else if (WIFSIGNALED(ms->err_tmp))
	{
		ms->err_tmp = WTERMSIG(ms->err_tmp) + 128;
	}
}
