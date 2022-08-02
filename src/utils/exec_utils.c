/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:21:28 by llima-ce          #+#    #+#             */
/*   Updated: 2022/08/02 12:19:39 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	exec_elf(t_cmd *cmd)
{
	char	*tmp;
	char	*s;

	if (ft_strncmp("./", cmd->line_cmd, 2) == 0)
	{
		s = get_cwd();
		tmp = ft_formatf("%s/%s", s, &cmd->line_cmd[2]);
		cmd->line_cmd = tmp;
		free_ptr((void **) &s);
	}
}

int	dup_custom(int fd1, int fd2)
{
	char	*tmp;

	if (dup2(fd1, fd2) == -1)
	{
		tmp = ft_formatf("minishell: %s : %i: %i", strerror(errno), fd1, fd2);
		ft_putstr_fd(tmp, STDERR_FILENO);
		free_ptr((void **) &tmp);
		return (-1);
	}
	return (0);
}

int	command_not_found(t_ms *ms, char *err)
{
	custom_perror(&ms->err_tmp, 1, " command not found", err);
	return (127);
}

static int	free_path(char **paths, int i, int res)
{
	while (paths[i] != NULL)
	{
		free_ptr((void **)&paths[i]);
		i++;
	}
	free_ptr((void **)&paths);
	return (res);
}

int	testing_access(t_cmd *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	if (access(cmd->argv[0], X_OK) == 0)
	{
		cmd->path_cmd = ft_strdup(cmd->argv[0]);
		return (0);
	}
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
