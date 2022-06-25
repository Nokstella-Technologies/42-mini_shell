/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:38 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/21 23:38:10 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"

static char	*concat(char **argv, char *formated, int i)
{
	char	*tmp;
	char	*text;

	text = ft_strdup("");
	while (argv[i] != NULL)
	{
		tmp = text;
		formated = verify_text(argv[i]);
		if (formated == NULL)
			return (NULL);
		if (*text == '\0')
			text = ft_formatf("%s%s", text, formated);
		else
			text = ft_formatf("%s %s", text, formated);
		i++;
		free_ptr((void **)&tmp);
		free_ptr((void **)&formated);
	}
	return (text);
}

void	command_echo(t_cmd *cmd)
{
	char	*text;
	int		i;

	i = 1;
	if (!cmd->argv[1])
		printf("\n");
	if (ft_strnstr(cmd->argv[1], "-n", 3))
		i = 2;
	text = concat(cmd->argv, NULL, i);
	if (text == NULL)
	{
		printf("minishell: echo: close your quotes\n");
		return ;
	}
	else if (ft_strnstr(cmd->argv[1], "-n", 3))
		printf("%s", text);
	else
		printf("%s\n", text);
	free_ptr((void **)&text);
}
