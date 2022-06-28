/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:18:56 by llima-ce          #+#    #+#             */
/*   Updated: 2022/06/28 13:40:44 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_fds
{
	int	in_fd;
	int	out_fd;
	int	tmp_out;
	int	heredoc_fd;
	int	fd[2];
}		t_fds;

typedef struct s_cmd
{
	char	*line_cmd;
	char	*path_cmd;
	char	**argv;
}			t_cmd;

int		testing_access(t_cmd *cmd);
int		find_cmd(t_cmd *cmd);
void	command_not_found(t_cmd *cmd);
int		dup_custom(int fd1, int fd2);

#endif