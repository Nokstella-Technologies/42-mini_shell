/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/15 01:25:08 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

static void	end_program(t_ms *ms)
{
	char	*line;

	dup_custom(ms->fd_origin[0], STDIN_FILENO);
	dup_custom(ms->fd_origin[1], STDOUT_FILENO);
	close(ms->fd_origin[0]);
	close(ms->fd_origin[1]);
	line = get_next_line(ms->fd.in_fd);
	while(line != NULL)
	{
		ft_putstr_fd(line, ms->fd.out_fd);
		free_ptr((void **)&line);
		line = get_next_line(ms->fd.in_fd);
	}
	close(ms->fd.in_fd);
}

// -> tokenin 
// -> verify handlers
// -> parse cmds
// -> exec
// -> end program

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
			end_program(ms);
		}
	}
	exit(0);
}
