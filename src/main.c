/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/09 22:09:42 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**g_envp;

int	main(int argc, char **argv, char **envp)
{
	int			exit_status[1];

	(void)argc;
	(void)argv;
	*exit_status = 0;
	g_envp = create_envp(envp);
	ft_sigaction();
	while (1)
	{
		if (mini_shell(exit_status) == TRUE)
			break ;
	}
	free_g_envp();
	ft_printf("\n");
	exit (errno);
}
