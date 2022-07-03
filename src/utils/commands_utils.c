/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 02:25:24 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/03 05:25:46 by llima-ce         ###   ########.fr       */
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

static char	*format_env(char *env_end, char *env_sign, char *env_start)
{
	char	*env;

	env = getenv(env_end);
	if (env)
	{
		if (ft_strfstr(env_sign + 1, "$ ") == NULL)
			return (ft_formatf("%s%s", env_start, env));
		else
			return (ft_formatf("%s%s%s", env_start, env,
					ft_strfstr(env_sign + 1, " $")));
	}
	else
	{
		if (ft_strfstr(env_sign + 1, " $") == NULL)
			return (ft_formatf("%s", env_start));
		else
			return (ft_formatf("%s%s", env_start,
					ft_strfstr(env_sign + 1, " $")));
	}
}

char	*sub_env(char *text, char *tmp)
{
	char	*env_start;
	char	*env_sign;
	char	*env_end;

	env_sign = ft_strchr(tmp, '$');
	while (env_sign)
	{
		env_start = ft_substr(tmp, 0, env_sign - tmp);
		env_end = ft_substr(env_sign, 1,
				ft_strfstr(env_sign + 1, "$ ") - env_sign - 1);
		text = tmp;
		tmp = format_env(env_end, env_sign, env_start);
		free_ptr((void **)&text);
		free_ptr((void **)&env_start);
		free_ptr((void **)&env_end);
		env_sign = ft_strchr(tmp, '$');
	}
	return (tmp);
}
