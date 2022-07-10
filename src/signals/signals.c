/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:55:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/10 15:24:25 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handler_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_sigaction(t_sigaction *sa, void (*hd)(int), int sig)
{
	sa->sa_handler = hd;
	sa->sa_flags = SA_RESTART;
	sigemptyset(&sa->sa_mask);
	sigaction(sig, sa, NULL);
}

void	ft_sigaction()
{
	t_sigaction	sa;

	init_sigaction(&sa, &handler_sig, SIGINT);
	init_sigaction(&sa, SIG_IGN, SIGQUIT);
}
