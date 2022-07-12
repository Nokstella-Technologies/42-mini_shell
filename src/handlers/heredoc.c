/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:50 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/12 17:03:55 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	heredoc_helper(t_ms *ms, char *final, char *r)
{
	char *tmp;

	tmp = ft_formatf("%s\n", r);
	final = verify_quotes(tmp, 0);
	ft_putstr_fd(final, ms->fd.heredoc_fd);
	free_ptr((void **)&final);
	free_ptr((void **)&tmp);
}

static void	error_heredoc(t_ms *ms, char *str)
{
	char	*tmp;

	tmp = ft_formatf("warning: here-document delimited by end-of-file (wanted `%s')", str);
	custom_perror(ms->err, 0, tmp, "heredoc");
	free_ptr((void **) &tmp);
}

void	heredoc(t_ms *ms, t_cmd *eof)
{
	char	*r;
	char	*prompt;

	ft_sigaction();
	r = NULL;
	while (1)
	{
		if (r != NULL)
			free_ptr((void **)&r);
		prompt = ft_formatf("> ");
		r = readline(prompt);
		free_ptr((void **)&prompt);
		if (r == NULL)
			return (error_heredoc(ms, eof->line_cmd));
		else if (ft_strncmp(eof->line_cmd, r, ft_strlen(r)) == 0)
		{
			free_ptr((void **)&r);
			break ;
		}
		else
		{
			heredoc_helper(ms, NULL, r);
		}
	}
}
