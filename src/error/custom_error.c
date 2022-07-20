/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:08:12 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/19 21:52:21 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	custom_perror(int *ms_err, int err, char *str, char *cmd)
{
	*ms_err = err;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	token_res(t_ms *ms, char *str)
{
	char	*tmp;

	if (ft_strncmp(str, "newline", 7) == 0)
		tmp = ft_formatf("syntax error near unexpected token `newline'");
	else if (*str == 't')
		tmp = ft_formatf("syntax error near unexpected token `>>'");
	else
		tmp = ft_formatf("syntax error near unexpected token `%c'", *str);
	custom_perror(ms->err, 2, tmp, NULL);
	free_ptr((void **)& tmp);
}

void	error_token(t_ms *ms)
{
	int		a;

	a = 0;
	while (ms->handlers[a] != 0)
	{
		if (a == 0 && (ms->handlers[a] == '|'))
			return (token_res(ms, &ms->handlers[a]));
		if ((ms->handlers[a] == '>' || ms->handlers[a] == '<'
				|| ms->handlers[a] == 't' || ms->handlers[a] == 'h')
			&& ms->handlers[a + 1] == 0)
			return (token_res(ms, "newline"));
		if ((ms->handlers[a] == '|') && (ms->handlers[a + 1] == '|'
				|| ms->handlers[a + 1] == 'o' || ms->handlers[a + 1] == 'a'))
			return (token_res(ms, &ms->handlers[a + 1]));
		if ((ms->handlers[a] == '>' || ms->handlers[a] == '<'
				|| ms->handlers[a] == 't' || ms->handlers[a] == 'h')
			&& (ms->handlers[a + 1] != 'f'))
			return (token_res(ms, &ms->handlers[a + 1]));
		a++;
	}
}
