/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:38 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/22 01:37:44 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	remove_envp(char *field)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(field);
	while (g_envp[i] != NULL)
	{
		if (!ft_strncmp(g_envp[i], field, len) && g_envp[i + 1] != NULL)
		{
			tmp = g_envp[i];
			g_envp[i] = g_envp[i + 1];
			g_envp[i + 1] = tmp;
		}
		i++;
	}
	if (!ft_strncmp(g_envp[i - 1], field, len))
		free_ptr((void **)&g_envp[i - 1]);
}

void	command_unset(t_cmd *cmd)
{
	char	*text;
	int		i;

	i = 1;
	while(cmd->argv[i] != NULL)
	{
		text = verify_text(cmd->argv[i]);
		if (text == NULL)
			printf("minishell: export: close your quotes\n");
		else if(ft_strchr(text, '='))
			printf("unset: `a=': not a valid identifier\n");
		else
			remove_envp(text);
		free_ptr((void **)&text);
		i++;
	}
}
