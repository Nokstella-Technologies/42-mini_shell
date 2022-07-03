/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/03 20:02:17 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**g_envp;

static char	**create_envp(char **envp)
{
	char	**tmp;
	int		a;

	a = 0;
	while (envp[a] != NULL)
		a++;
	tmp = (char **)malloc((a + 1) * sizeof(char *));
	a = 0;
	while (envp[a] != NULL)
	{
		tmp[a] = ft_strdup(envp[a]);
		a++;
	}
	tmp[a] = NULL;
	return (tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_sigaction	sa;
	int			exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	g_envp = create_envp(envp);
	init_sigaction(&sa, &handler_sig, SIGINT);
	init_sigaction(&sa, SIG_IGN, SIGQUIT);
	while (1)
	{
		if (mini_shell(&exit_status) == TRUE)
			break ;
	}
	free_g_envp();
	exit (exit_status);
}
