/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:34 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/21 19:50:58 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	command_exit(t_ms *ms)
{
	custom_close(&ms->fd.in_fd);
	ms->fd.in_fd = ms->fd.fd[0];
	custom_close(&ms->fd.fd[1]);
	end_program(&ms);
	exit(0);
}
