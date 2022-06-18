/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:20:06 by llima-ce          #+#    #+#             */
/*   Updated: 2022/06/18 16:10:21 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void custom_close(int *fd)
{
	int err;
	char *tmp;
	
	err = close(*fd);
	if (err == -1)
	{

		tmp = ft_formatf("minishell: %s\n", strerror(errno));
		perror(tmp);
		free_ptr((void **) &tmp);
		*fd = -1;
	}
	else 
	{
		*fd = 0;
	}
}

void	end_program(t_ms **ms)
{
	// char	*line;

	// line = NULL;
	if(ms[0]->fd.fd[0] != 0)
		custom_close(&ms[0]->fd.fd[0]);
	if(ms[0]->fd.fd[1] != 0)
		custom_close(&ms[0]->fd.fd[1]);
	dup_custom(ms[0]->fd_origin[0], STDIN_FILENO);
	dup_custom(ms[0]->fd_origin[1], STDOUT_FILENO);
	custom_close(&ms[0]->fd_origin[0]);
	custom_close(&ms[0]->fd_origin[1]);
	// custom_close(&ms[0]->fd.fd[0]);
	// if (ms[0]->err == 0)
	// {
	// 	line = get_next_line(ms[0]->fd.in_fd);
	// 	while(line != NULL)
	// 	{
	// 		ft_putstr_fd(line, ms[0]->fd.out_fd);
	// 		free_ptr((void **)&line);
	// 		line = get_next_line(ms[0]->fd.fd[0]);
	// 	}
	// }
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
		if(ms[0]->cmd[i]->argv != NULL)
		{
			while (ms[0]->cmd[i]->argv[j] != NULL)
			{
				free_ptr((void **)&ms[0]->cmd[i]->argv[j]);
				j++;
			}
		}
		free_ptr((void **)&ms[0]->cmd[i]->argv);
		free_ptr((void **)&ms[0]->cmd[i]);
		i++;
	}
	free_ptr((void **)&ms[0]->cmd);
	free_ptr((void **)&ms[0]);
}
