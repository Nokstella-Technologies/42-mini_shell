/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/05 23:22:05 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	t_sigaction	sa;
	int			exit_status[1];

	(void)argc;
	(void)argv;
	*exit_status = 0;
	g_envp = create_envp(envp);
	init_sigaction(&sa, &handler_sig, SIGINT);
	init_sigaction(&sa, SIG_IGN, SIGQUIT);
	while (1)
	{
		if (mini_shell(exit_status) == TRUE)
			break ;
	}
	// printf("%d, %d\n", errno, *exit_status);
	free_g_envp();
	exit (errno);
}
