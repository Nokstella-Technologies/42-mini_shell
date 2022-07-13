/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:58:17 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/12 19:01:49 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	history_initialization(void)
{
	char	*history;
	int		fd;
	int		i;

	fd = open(".mini_history", O_RDONLY);
	if (fd == -1)
		return ;
	history = get_next_line(fd);
	i = 0;
	while(history != NULL)
	{
		add_history(history);
		free_ptr((void **)&history);
		history = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	command_history(t_ms *ms)
{
	int		fd;
	int		i;
	char	*line;

	(void) ms;
	fd = open(".mini_history", O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	i = 1;
	while (line != NULL)
	{
		printf("%d %s", i, line);
		free_ptr((void **)&line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	history(char *r)
{
	int	fd;

	add_history(r);
	fd = open(".mini_history", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return ;
	write(fd, r, ft_strlen(r));
	write(fd, "\n", 1);
	close(fd);
}
