/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/21 21:23:55 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"


// -> tokenin 
// -> verify handlers
// -> parse cmds
// -> exec
// -> end program

void mini_shell(void)
{
	char	*s;
	char	*prompt;
	char	*r;
	t_ms	*ms;

	r = ft_strdup("");
	while(r != NULL)
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
		else
		{
			add_history(r);
			ms = init_struct(r);
			tokeneer(ms, r, 0, NULL);
			if (ms->err == -2)
			{
				error_token(ms);
				continue;
			}
			pipe(ms->fd.fd);
			exec_command(ms->cmd[0], ms);
			end_program(&ms);
		}
	}
	free_g_envp();
	free_ptr((void **)&r);
	exit(0);
}
