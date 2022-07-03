/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:20:06 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/03 05:33:29 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	custom_close(int *fd)
{
	int		err;
	char	*tmp;

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
	if (ms[0]->fd.fd[0] != 0)
		custom_close(&ms[0]->fd.fd[0]);
	if (ms[0]->fd.fd[1] != 0)
		custom_close(&ms[0]->fd.fd[1]);
	dup_custom(ms[0]->fd_origin[0], STDIN_FILENO);
	dup_custom(ms[0]->fd_origin[1], STDOUT_FILENO);
	custom_close(&ms[0]->fd_origin[0]);
	custom_close(&ms[0]->fd_origin[1]);
	free_all(&ms[0]);
	errno = 0;
}

void	free_g_envp(void)
{
	int	i;

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
	int	i;
	int	j;

	free_ptr((void **)&ms[0]->handlers);
	free_ptr((void **)&ms[0]->line);
	i = 0;
	while (ms[0]->cmd[i] != NULL)
	{
		j = 0;
		free_ptr((void **)&ms[0]->cmd[i]->line_cmd);
		free_ptr((void **)&ms[0]->cmd[i]->path_cmd);
		if (ms[0]->cmd[i]->argv != NULL)
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
