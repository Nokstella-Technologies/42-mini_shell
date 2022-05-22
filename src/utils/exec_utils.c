/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:21:28 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/21 23:57:56 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	dup_custom(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

void	command_not_found(t_cmd *cmd)
{
	
	printf("%s: command not found\n", cmd->argv[0]);
}

static int free_path(char **paths, int i, int res)
{
	while(paths[i] != NULL)
	{
		free_ptr((void **)&paths[i]);
		i++;
	}
	free_ptr((void **)&paths);
	return(res);
}

int	testing_access(t_cmd *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		cmd->path_cmd = ft_formatf("%s/%s", paths[i],
				cmd->argv[0]);
		if (access(cmd->path_cmd, X_OK) == 0)
			return (free_path(paths, 0, 0));
		free_ptr((void **)&cmd->path_cmd);
		i++;
	}
	return (free_path(paths, 0, 2));
}