/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/29 10:46:05 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	mini_shell(void)
{
	char	*s;
	char	*prompt;
	char	*r;
	t_ms	*ms;

	r = ft_strdup("");
	while (r != NULL)
	{
		if (r)
			free_ptr((void **)&r);
		s = get_cwd();
		prompt = ft_formatf("%s@%s:%s$ ", getenv("LOGNAME"), WORKSPACE, s);
		r = readline(prompt);
		free_ptr((void **)&prompt);
		free_ptr((void **)&s);
		if (!r)
			printf("\n");
		else if (*r != 0)
		{
			history(ms, r);
			ms = init_struct(r);
			tokeneer(ms, r, 0, NULL);
			if (ms->err == -2)
			{
				error_token(ms);
				continue ;
			}
			verify_next_move(ms);
			end_program(&ms);
		}
	}
	perror(strerror(errno));
	free_g_envp();
	free_ptr((void **)&r);
	exit (0);
}
