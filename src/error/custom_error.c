/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:08:12 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/05 19:42:58 by llima-ce         ###   ########.fr       */
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

void	error_token(t_ms *ms)
{
	int	a;

	a = 0;
	while (ms->handlers[a] != 0)
	{
		if (a == 0 && (ms->handlers[a] == '|' || ms->handlers[a] == 'o'
				|| ms->handlers[a] == 'a'))
			custom_perror(ms, 2, "error tokenizer");
		else if (ms->handlers[a] == '|' || ms->handlers[a] == 'o'
			|| ms->handlers[a] == 'a' || ms->handlers[a] == '>'
			|| ms->handlers[a] == '<' || ms->handlers[a] == 't'
			|| ms->handlers[a] == 'h')
		{
			if (ms->handlers[a + 1] == '|' || ms->handlers[a + 1] == 'o'
				|| ms->handlers[a + 1] == 'a' || ms->handlers[a + 1] == '>'
				|| ms->handlers[a + 1] == '<' || ms->handlers[a + 1] == 't'
				|| ms->handlers[a + 1] == 'h')
				custom_perror(ms, 2,"error tokenizer");
		}
		a++;
	}
}
