/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:55:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/04/05 21:31:29 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void handler_sig(int sig)
{
	char s[100];
	
	if (sig == SIGINT)
		printf("\n%s@%s:%s$ ", getenv("LOGNAME"), WORKSPACE, getcwd(s, 100));
}

void init_sigaction(t_sigaction *sa, void (*hd)(int), int sig)
{
	sa->sa_handler = hd;
	sa->sa_flags = SA_RESTART;
	sigemptyset(&sa->sa_mask);
	sigaction(sig, sa, NULL);
}