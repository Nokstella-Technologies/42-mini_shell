/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:58:17 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/13 19:04:01 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	history_initialization(void)
{
	char	*history;
	char	*tmp;
	int		fd;
	int		i;

	fd = open(".mini_history", O_RDONLY);
	if (fd == -1)
		return ;
	history = get_next_line(fd);
	i = 0;
	while(history != NULL)
	{
		tmp = ft_substr(history, 0, ft_strlen(history) - 1);
		free_ptr((void **)&history);
		add_history(tmp);
		free_ptr((void **)&tmp);
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
