/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/27 18:48:54 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	t_sigaction	sa;
	int			exit_status[1];

	(void)argv;
	if (argc != 1)
	{
		perror("minishell: many argments\n");
		return(1);
	}	
	*exit_status = 0;
	g_envp = create_envp(envp);
	history_initialization();
	while (1)
	{
		init_sigaction(&sa, &handler_sig, SIGINT);
		init_sigaction(&sa, SIG_IGN, SIGQUIT);
		if (mini_shell(exit_status, &sa) == TRUE)
			break ;
	}
	rl_clear_history();
	free_g_envp();
	printf("\n");
	return (*exit_status);
}
