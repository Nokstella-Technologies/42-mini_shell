/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:55:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/08/02 11:52:15 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handler_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_sig_child(int sig)
{
	if (sig == SIGINT)
		exit(0);
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

void	handle_child_sig_int_here_doc(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	exit(130);
}

void	init_sigaction(t_sigaction *sa, void (*hd)(int), int sig)
{
	sa->sa_handler = hd;
	sa->sa_flags = SA_RESTART;
	sigemptyset(&sa->sa_mask);
	sigaction(sig, sa, NULL);
}
