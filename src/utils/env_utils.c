/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:04:37 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/05 23:22:03 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_cwd(void)
{
	char	*tmp;
	int		a;

	a = 1;
	tmp = NULL;
	while (tmp == NULL)
	{
		tmp = ft_calloc(((BUFFER * a) + 1), sizeof(char));
		if (getcwd(tmp, (BUFFER * a)) == NULL)
			free(tmp);
		a++;
	}
	return (tmp);
}

char	**create_envp(char **envp)
{
	char	**tmp;
	int		a;

	a = 0;
	while (envp[a] != NULL)
		a++;
	tmp = (char **)malloc((a + 1) * sizeof(char *));
	a = 0;
	while (envp[a] != NULL)
	{
		tmp[a] = ft_strdup(envp[a]);
		a++;
	}
	tmp[a] = NULL;
	return (tmp);
}


void	set_env(char *name, char *value)
{
	char	**tmp;
	int		i;

	i = 0;
	while (g_envp[i] != NULL && ft_strnstr(g_envp[i], name,
			ft_strlen(name)) == NULL)
		i++;
	if (g_envp[i] != NULL)
	{
		free_ptr((void **)&g_envp[i]);
		g_envp[i] = ft_formatf("%s=%s", name, value);
		return ;
	}
	tmp = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (g_envp[i] != NULL)
	{
		tmp[i] = g_envp[i];
		i++;
	}	
	free_ptr((void **)&g_envp);
	g_envp = tmp;
	g_envp[i] = ft_formatf("%s=%s", name, value);
	g_envp[i + 1] = NULL;
}

char	*get_envp(char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(var, "=");
	while (g_envp[i] != NULL)
	{
		if (ft_strncmp(g_envp[i], tmp, ft_strlen(var) + 1) == 0)
		{
			free_ptr((void **)&tmp);
			return(ft_strdup(&g_envp[i][ft_strlen(var) + 1]));
		}
		i++;
	}
	free_ptr((void **)&tmp);
	return (NULL);
}