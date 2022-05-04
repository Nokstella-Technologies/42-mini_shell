/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/18 21:04:23 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


char **g_envp;

// signal
// sigaction
// sigemptyset
// sigaddset

int	main(int argc, char **argv, char **envp)
{
	t_sigaction sa;
	(void)argc;
	(void)argv;

	g_envp = envp;
	init_sigaction(&sa, &handler_sig, SIGINT);
	init_sigaction(&sa, SIG_IGN, SIGQUIT);
	while(1)
		mini_shell();
	return 0;
}

// testar >|<
/*
echo -n "asdkmoasjdnasnd" | grep a > teste
cd 
pwd
export
unset
env
exit
history
manusear single quotes
manusear double quotes com do $
executer ./
<<
>>
<
>
Ctrl D, Ctrl C, Ctrl \
**BONUS**
||
&&
Wildcard * working for the current dir
*/