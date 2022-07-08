/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:08:12 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/08 13:03:44 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	custom_perror(t_ms *ms, int err, char *str)
{
	errno = err;
	ms->err[0] = err;
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void tonken_res(t_ms *ms ,char *str)
{
	char	*tmp;

	if (ft_strncmp(str,"newline", 7) == 0)
		tmp = ft_formatf(" syntax error near unexpected token `newline'");
	else if (*str == 't')
		tmp = ft_formatf(" syntax error near unexpected token `>>'");
	else
		tmp = ft_formatf(" syntax error near unexpected token `%c'", *str);
	custom_perror(ms, 2, tmp);
	free_ptr((void **)& tmp);
}

void	error_token(t_ms *ms)
{
	int		a;

	a = 0;
	while (ms->handlers[a] != 0)
	{
		if (a == 0 && (ms->handlers[a] == '|' || ms->handlers[a] == 'o'
				|| ms->handlers[a] == 'a'))
			return (tonken_res(ms, &ms->handlers[a]));
		if ((ms->handlers[a] == '>' || ms->handlers[a] == '<'
			|| ms->handlers[a] == 't' || ms->handlers[a] == 'h')
			&& ms->handlers[a + 1] == 0)
			return (tonken_res(ms, "newline"));
		if ((ms->handlers[a] == '|' || ms->handlers[a] == 'o'
			|| ms->handlers[a] == 'a') && (ms->handlers[a + 1] == '|'
			|| ms->handlers[a + 1] == 'o' || ms->handlers[a + 1] == 'a'))
			return (tonken_res(ms, &ms->handlers[a + 1]));
		if ((ms->handlers[a] == '>' || ms->handlers[a] == '<'
			|| ms->handlers[a] == 't' || ms->handlers[a] == 'h')
			&& (ms->handlers[a + 1] != 'f'))
			return (tonken_res(ms, &ms->handlers[a + 1]));
		a++;
	}
}
