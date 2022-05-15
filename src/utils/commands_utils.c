/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 02:25:24 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/15 03:20:00 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_cwd(void)
{
	char	*tmp;
	int		a;

	a = 1;
	tmp = NULL;
	while(tmp == NULL)
	{
		tmp = ft_calloc(((BUFFER * a) + 1), sizeof(char));
		if(getcwd(tmp, (BUFFER * a)) == NULL)
			free(tmp);
		a++;
	}
	return (tmp);
}

void	set_env(char *name, char *value)
{
	char	**tmp;
	int		i;

	setenv(name, value, 1);
	i = 0;
	while (g_envp[i] != NULL && ft_strnstr(g_envp[i], name, ft_strlen(name)) == NULL)
		i++;
	if (g_envp != NULL)
	{
		free(g_envp[i]);
		g_envp[i] = ft_formatf("%s=%s", name, value);
		return ;
	}
	tmp = malloc((i + 2)*sizeof(char *));
	i = 0;
	while (g_envp[i] != NULL)
		tmp[i] = g_envp[i];
	free(g_envp);
	g_envp = tmp;
	g_envp[i] = ft_formatf("%s=%s",name, value);
	g_envp[i + 1] = NULL;
}