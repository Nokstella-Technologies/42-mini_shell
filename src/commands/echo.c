/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:38 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/09 15:36:09 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"

static char	*concat(char **argv, t_bool flag, int i)
{
	char	*tmp;
	char	*text;

	text = ft_strdup("");
	while (argv[i] != NULL)
	{
		tmp = text;
		if (*text == '\0')
			text = ft_formatf("%s%s", text, argv[i]);
		else
			text = ft_formatf("%s %s", text, argv[i]);
		free_ptr((void **)&tmp);
		i++;
	}
	tmp = text;
	if (!flag)
	{
		text = ft_formatf("%s\n", text);
		free_ptr((void **)&tmp);
	}
	return (text);
}

void	command_echo(t_ms *ms)
{
	char	*text;
	int		i;

	i = 1;
	if (ms->cmd[ms->cmd_now]->argv[1] == 0)
	{
		ft_printf("\n");
		return ;
	}
	else if (ft_strnstr(ms->cmd[ms->cmd_now]->argv[1], "-n", 3))
		text = concat(ms->cmd[ms->cmd_now]->argv, TRUE, i);
	else 
		text = concat(ms->cmd[ms->cmd_now]->argv, FALSE, i);
	if (text == NULL)
	{
		custom_perror(ms, 1, "Not Possible to write this phrase");
		return ;
	}
	ft_printf("%s", text);
	free_ptr((void **)&text);
}
