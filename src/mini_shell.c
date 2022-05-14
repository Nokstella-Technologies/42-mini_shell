/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/03 11:45:02 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

void mini_shell(void)
{
	char s[100];
	char *prompt;
	char *r;
	t_ms *ms;

	r = ft_strdup("");
	while(r != NULL)
	{
		if (r)
			free_ptr((void **)&r);
		getcwd(s, 100);
		prompt = ft_formatf("%s@%s:%s$ ", getenv("LOGNAME"), WORKSPACE, s);
		r = readline(prompt);
		free_ptr((void **)&prompt);
		if (!r)
			printf("\n");
		else if (!ft_strncmp(r, "exit", 4))
			exit(0);
		// else if(!ft_strncmp(r, "env",3))
		// 	command_env();
		else
		{
			add_history(r);
			ms = init_struct(r);
			parse_string(ms, r, 0, NULL);
			if (ms->err == -2)
			{
				error_token(ms);
				continue;
			}
			exec_line(ms);
		}
	}
	exit(0);
}
