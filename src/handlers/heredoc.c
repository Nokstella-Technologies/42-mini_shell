/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:50 by vantonie          #+#    #+#             */
/*   Updated: 2022/08/02 12:19:39 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	heredoc_helper(t_ms *ms, char *final, char *r)
{
	char	*tmp;

	tmp = ft_formatf("%s\n", r);
	final = verify_quotes(tmp, 0, ms->err[0]);
	ft_putstr_fd(final, ms->fd.heredoc_fd);
	free_ptr((void **)&final);
	free_ptr((void **)&tmp);
}

static void	error_heredoc(t_ms *ms, int *f)
{
	char	*tmp;

	tmp = ft_formatf(
			"warning: here-document delimited by end-of-file (wanted `%s')",
			ms->cmd[ms->cmd_now + *f]->line_cmd);
	custom_perror(&ms->err_tmp, 0, tmp, "heredoc");
	free_ptr((void **) &tmp);
}

void	heredoc(t_ms *ms, int *f)
{
	char	*r;

	init_sigaction(ms->sa, handle_child_sig_int_here_doc, SIGINT);
	init_sigaction(ms->sa, SIG_IGN, SIGQUIT);
	r = NULL;
	while (1)
	{
		r = readline("> ");
		if (r == NULL)
			return (error_heredoc(ms, f));
		else if (ft_strncmp(ms->cmd[ms->cmd_now + *f]->line_cmd, r,
				ft_strlen(r) + 1) == 0)
		{
			free_ptr((void **)&r);
			exit(ms->err_tmp);
		}
		else if (ft_strlen(r) != 0)
			heredoc_helper(ms, NULL, r);
		free_ptr((void **)&r);
	}
}
