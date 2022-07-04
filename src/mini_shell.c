/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/04 11:58:42 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char *read_line(char *prompt, char *s,char *workspacename) {
	int		fd;
	char	*r;
	char	*tmp;

	s = get_cwd();
	tmp = ft_substr(s, ft_strlen(getenv("HOME")), ft_strlen(s));
	free_ptr((void **)&s);
	s = ft_strjoin("~", tmp);
	free_ptr((void **)&tmp);
	fd = open("/etc/hostname", O_RDONLY, 0644);
	workspacename = get_next_line(fd);
	tmp = ft_strjoin(workspacename, "\0");
	free_ptr((void **)&workspacename);
	workspacename = ft_strtrim(tmp, "\n");
	prompt = ft_formatf("%s@%s:%s$ ", getenv("USER"), workspacename, s);
	r = readline(prompt);
	free_ptr((void **)&s);
	free_ptr((void **)&tmp);
	free_ptr((void **)&workspacename);
	free_ptr((void **)&prompt);
	close(fd);
	return (r);
}


t_bool	mini_shell(int *err)
{
	char		*r;
	t_ms		*ms;

	r = read_line(NULL, NULL, NULL);
	if (!r)
		return (TRUE);
	else if (*r != 0)
	{
		history(r);
		ms = init_struct(r, err);
		tokeneer(ms, r, 0, NULL);
		if (ms->err[0] == -2)
		{
			error_token(ms);
			return (FALSE);
		}
		verify_next_move(ms);
		end_program(&ms);
		free_ptr((void **)&r);
		return (FALSE);
	}
	free_ptr((void **) &r);	
	return (FALSE);
}
