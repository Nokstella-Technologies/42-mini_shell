/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:18:56 by llima-ce          #+#    #+#             */
/*   Updated: 2022/04/12 20:02:33 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include "../libft/libft.h"

# define PATHS ft_split(getenv("PATH"), ':')

typedef struct s_fds
{
	int in_fd;
	int out_fd;
	int fd[2];
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
int		dup_custom(int fd1, int fd2, t_cmd *cmd);
#endif