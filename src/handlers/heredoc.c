/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:50 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/28 12:21:15 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	heredoc_helper(t_ms *ms, char *final, char *r)
{
	if (*r == 0)
	{
		free_ptr((void **)&r);
		r = ft_formatf("\n");
	}
	ms->fd.heredoc_fd = open("./.tmp", O_RDWR | O_CREAT, 0644);
	final = verify_quotes(r, 0);
	ft_putstr_fd(final, ms->fd.heredoc_fd);
	ft_putstr_fd("\n", ms->fd.heredoc_fd);
	free_ptr((void **)&r);
	free_ptr((void **)&final);
}

void	heredoc(t_ms *ms, t_cmd *eof)
{
	char	*r;
	char	*prompt;
	char	*final;

	r = ft_strdup("");
	final = NULL;
	while (r != NULL)
	{
		if (r)
			free_ptr((void **)&r);
		prompt = ft_formatf("> ");
		r = readline(prompt);
		free_ptr((void **)&prompt);
		if (ft_strncmp(eof->line_cmd, r, ft_strlen(r)) == 0)
		{
			free_ptr((void **)&r);
			break ;
		}
		else
		{
			heredoc_helper(ms, final, r);
		}
	}
}
