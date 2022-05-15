/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:40 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/15 03:23:16 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char *verify_text(char *text)
{
	char *tmp;

	if (*text == '\'')
		return(ft_strtrim(text, "\'"));
	else {
		tmp = ft_strtrim(text, "\"");
		return (tmp);
	}
}

void	command_export(t_cmd *cmd)
{	
	char	**splitted;
	char	*value;
	int		i;

	i = 1;
	while(cmd->argv[i] == NULL)
	{
		if(ft_strchr(cmd->argv[i], '='))
		{
			splitted = ft_split(cmd->argv[1], '=');
			if (ft_strchr(splitted[0], ' ') == NULL)
				printf("%s\n", strerror(errno));
			if (splitted[1] == NULL)
				set_env(splitted[0], "");
			value =  verify_text(splitted[1]);
			set_env(splitted[0], value);
		}
	}
}

// parse "luiz='teste'" luiz=$PWD