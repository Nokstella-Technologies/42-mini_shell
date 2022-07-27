/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/27 11:29:45 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*read_line(char *prompt, char *s, char *work_space_name)
{
	int		fd;
	char	*r;
	char	*tmp;

	s = get_cwd();
	if (!strncmp(s, getenv("HOME"), ft_strlen(getenv("HOME")) + 1))
	{
		tmp = ft_substr(s, ft_strlen(getenv("HOME")), ft_strlen(s));
		free_ptr((void **)&s);
		s = ft_strjoin("~", tmp);
		free_ptr((void **)&tmp);
	}
	fd = open("/etc/hostname", O_RDONLY, 0644);
	work_space_name = get_next_line(fd);
	tmp = ft_strjoin(work_space_name, "\0");
	free_ptr((void **)&work_space_name);
	work_space_name = ft_strtrim(tmp, "\n");
	prompt = ft_formatf("%s@%s:%s$ ", getenv("USER"), work_space_name, s);
	r = readline(prompt);
	free_ptr((void **)&s);
	free_ptr((void **)&tmp);
	free_ptr((void **)&work_space_name);
	free_ptr((void **)&prompt);
	close(fd);
	return (r);
}

t_bool	mini_shell(int *err, t_sigaction *sa)
{
	char		*r;
	t_ms		*ms;

	r = read_line(NULL, NULL, NULL);
	if (!r)
		return (TRUE);
	else if (*r != 0)
	{
		history(r);
		ms = init_struct(r, err, sa);
		tokeneer(ms, r, 0, NULL);
		if (ms->err[0] == -2)
		{
			error_token(ms);
			free_ptr((void **) &r);
			end_program(&ms);
			return (FALSE);
		}
		verify_next_move(ms);
		free_ptr((void **)&r);
		end_program(&ms);
		return (FALSE);
	}
	free_ptr((void **) &r);
	return (FALSE);
}
