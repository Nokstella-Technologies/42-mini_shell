/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:27:24 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/26 21:30:35 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_waitpid(t_ms *ms, int pid)
{
	wait4(pid, ms->err, 0, NULL);
	if (WIFEXITED(*ms->err))
		*ms->err = WEXITSTATUS(*ms->err);
	else if (WIFSIGNALED(*ms->err))
		*ms->err = WTERMSIG(*ms->err) + 128;
}
