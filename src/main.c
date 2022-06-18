/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/17 15:57:46 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


char **g_envp;

// signal
// sigaction
// sigemptyset
// sigaddset

static char **	create_envp(char **envp)
{
	char	**tmp;
	int		a;

	a = 0;
	while(envp[a] != NULL)
		a++;
	tmp = (char **)malloc((a + 1)* sizeof(char *));
	a = 0;
	while(envp[a] != NULL)
	{
		tmp[a] = ft_strdup(envp[a]);
		a++;
	}
	tmp[a] = NULL;
	return(tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_sigaction	sa;

	(void)argc;
	(void)argv;
	g_envp = create_envp(envp);
	init_sigaction(&sa, &handler_sig, SIGINT);
	init_sigaction(&sa, SIG_IGN, SIGQUIT);
	while (1)
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