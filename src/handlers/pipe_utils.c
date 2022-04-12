/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:21:28 by llima-ce          #+#    #+#             */
/*   Updated: 2022/04/12 18:51:55 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	dup_custom(int fd1, int fd2, t_cmd *cmd)
{
	if (dup2(fd1, fd2) == -1)
	{
		printf("%s\n", cmd->argv[0]);
		return (-1);
	}
	return (0);
}

void	command_not_found(t_cmd *cmd)
{
	printf("%s: command not found\n", cmd->argv[0]);
}

int	find_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (7);
	cmd->argv = ft_split_pipe(cmd->line_cmd);
	return (0);
}

int	testing_access(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (PATHS[i])
	{
		cmd->path_cmd = ft_formatf("%s/%s", PATHS[i],
				cmd->argv[0]);
		if (access(cmd->path_cmd, X_OK) == 0)
			return (0);
		free_ptr((void **)cmd->path_cmd);
		i++;
	}
	return (2);
}