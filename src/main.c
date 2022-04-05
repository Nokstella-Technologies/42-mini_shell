/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/05 19:03:48 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"


char **g_envp;

// signal
// sigaction
// sigemptyset
// sigaddset

void init_sigaction(t_sigaction *sa)
{
	sigaction();
}

int	main(int argc, char **argv, char **envp)
{
	t_sigaction sa;
	(void)argc;
	(void)argv;

	g_envp = envp;
	init_sigaction(&sa);
	while(1)
	{
		mini_shell();
	}
	return 0;
}


/*
echo -n
cd 
pwd
export
unset
env
exit
history
manusear single quotes
manusear double quotes com do $
executar ./
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