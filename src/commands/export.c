/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:40 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/22 00:11:03 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*verify_text(char *text)
{
	char	*tmp2;
	
	tmp2 = verify_quotes(text, 0);
	if (tmp2 == NULL)
		return (NULL);
	return (tmp2);
}

void	command_export(t_cmd *cmd)
{
	char	**splitted;
	char	*text;
	int		i;

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			text = verify_text(cmd->argv[i]);
			if (text == NULL)
				printf("minishell: export: close your quotes\n");
			splitted = ft_split(text, '=');
			if (ft_strchr(cmd->argv[i], '=') == cmd->argv[i] || ft_strchr(splitted[0], ' ') != NULL)
				printf("minishell: export: `=': not a valid identifier\n");
			else if (splitted[1] == NULL)
				set_env(splitted[0], "");
			else
				set_env(splitted[0], splitted[1]);
			free_ptr((void **)&text);
			free_ptr((void **)&splitted[0]);
			free_ptr((void **)&splitted[1]);
			free_ptr((void **)&splitted);
		}
		i++;
	}
}

// parse "luiz='teste'" luiz=$PWD
// commnad not found break (possible infinite loop)