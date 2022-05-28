/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an7onie77i <an7onie77i@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:20:06 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/28 17:39:00 by an7onie77i       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	end_program(t_ms **ms)
{
	char	*line;

	line = NULL;
	dup_custom(ms[0]->fd_origin[0], STDOUT_FILENO);
	dup_custom(ms[0]->fd_origin[1], STDIN_FILENO);
	close(ms[0]->fd_origin[0]);
	close(ms[0]->fd_origin[1]);
	if (ms[0]->err == 0)
	{
		line = get_next_line(ms[0]->fd.in_fd);
		while(line != NULL)
		{
			ft_putstr_fd(line, ms[0]->fd.out_fd);
			free_ptr((void **)&line);
			line = get_next_line(ms[0]->fd.fd[0]);
		}
	}
	close(ms[0]->fd.fd[0]);
	free_all(&ms[0]);
}

void	free_g_envp(void)
{
	int i;
	
	i = 0;
	while (g_envp[i] != NULL)
	{
		free_ptr((void **)&g_envp[i]);
		i++;
	}
	free_ptr((void **)&g_envp);
}

void	free_all(t_ms *ms[0])
{
	int i;
	int j;

	free_ptr((void **)&ms[0]->handlers);
	free_ptr((void **)&ms[0]->line);
	i = 0;
	while (ms[0]->cmd[i] != NULL)
	{
		j = 0;
		
		free_ptr((void **)&ms[0]->cmd[i]->line_cmd);
		free_ptr((void **)&ms[0]->cmd[i]->path_cmd);
		while (ms[0]->cmd[i]->argv[j] != NULL)
		{
			free_ptr((void **)&ms[0]->cmd[i]->argv[j]);
			j++;
		}
		free_ptr((void **)&ms[0]->cmd[i]->argv);
		free_ptr((void **)&ms[0]->cmd[i]);
		i++;
	}
	free_ptr((void **)&ms[0]->cmd);
	free_ptr((void **)&ms[0]);
}
