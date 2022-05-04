/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:32:05 by llima-ce          #+#    #+#             */
/*   Updated: 2022/04/18 22:08:38 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

t_ms *init_struct(char *line)
{
	t_ms *ms;

	ms = (t_ms *)malloc(sizeof(t_ms));
	ms->cmd = NULL;
	ms->line = line;
	ms->fd.in_fd = 0;
	ms->fd.out_fd = 1;
	ms->handlers = ft_strdup("");
	ms->err = 0;
	return(ms);
}
