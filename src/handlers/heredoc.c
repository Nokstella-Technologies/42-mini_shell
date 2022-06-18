/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:50 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/18 17:37:33 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void heredoc(t_ms *ms, t_cmd *eof)
{
	char	*r;
	char	*prompt;
	char	*final;
	
	r = ft_strdup("");
	while(r != NULL)
	{
		if(r)
			free_ptr((void **)&r);
		prompt = ft_formatf("> ");
		r = readline(prompt);
		free_ptr((void **)&prompt);
		if(ft_strncmp(eof->line_cmd, r, ft_strlen(r)) == 0)
		{
			free_ptr((void **)&r);
			break;
		}
		else
		{
			if(*r == 0)
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
	}
}
