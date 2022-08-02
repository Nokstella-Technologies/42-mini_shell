/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:12:04 by llima-ce          #+#    #+#             */
/*   Updated: 2022/08/02 11:31:11 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*format_env(char *env_sign, char *env_start, char *env,
char *env_end)
{
	char	*final;
	int		a;

	a = ft_strlen(env_start) + ft_strlen(env_end) + 1;
	if (env)
		final = ft_formatf("%s%s%s", env_start, env, &env_sign[a]);
	else
	{
		if (*(env_sign + 1) == 0 || *(env_sign + 1) == ' ')
			final = ft_formatf("%s%s%s", env_start, "$", &env_sign[a]);
		else if (*env_start != 0 && env_sign[a] != 0)
			final = ft_formatf("%s%s", env_start, &env_sign[a]);
		else
			return (ft_strdup(""));
	}
	free_ptr((void **) &env);
	return (final);
}

static char	*sub_env(char *text, char *tmp, int a, int err)
{
	char	*env_start;
	int		env_sign;
	char	*env_end;

	env_sign = ft_strchr(&tmp[a], '$') - tmp;
	if (env_sign >= 0)
	{
		env_start = ft_substr(tmp, 0, env_sign);
		env_end = ft_substr(tmp, env_sign + 1,
				ft_strfstr(&tmp[env_sign + 1], " $") - &tmp[env_sign] - 1);
		text = tmp;
		if (ft_strncmp(env_end, "?", 1) == 0)
			tmp = format_env(tmp, env_start, ft_itoa(err), "?");
		else
			tmp = format_env(tmp, env_start, get_envp(env_end), env_end);
		free_ptr((void **)&env_start);
		free_ptr((void **)&text);
		free_ptr((void **)&env_end);
		if (*tmp == 0)
			return (tmp);
		return (sub_env(NULL, tmp, env_sign + 1, err));
	}
	return (tmp);
}

static int	find_second_quote(char *sub, char quote, char **tmp, int err)
{
	int	i;

	i = 0;
	while (sub[i] != 0 && sub[i] != quote)
		i++;
	if (sub != &sub[i] && sub[i] == quote)
	{
		*tmp = ft_substr(sub, 0, i);
		if (quote == '\"')
			*tmp = sub_env(NULL, *tmp, 0, err);
		return (i + 2);
	}
	else
	{
		*tmp = ft_strdup("");
		return (1);
	}
}

static int	find_without_quote(char *sub, char **tmp, int err)
{
	int	i;

	i = 0;
	while (sub[i] && sub[i] != '\"' && sub[i] != '\'')
		i++;
	*tmp = ft_substr(sub, 0, i);
	*tmp = sub_env(NULL, *tmp, 0, err);
	return (i);
}

char	*verify_quotes(char *text, int i, int err)
{
	char	*sub;
	char	*end_text;
	char	*tmp;

	end_text = ft_strdup("");
	while (text[i] != 0)
	{
		if (text[i] == '\"' || text[i] == '\'')
			i += find_second_quote(text + i + 1, text[i], &sub, err);
		else
			i += find_without_quote(text + i, &sub, err);
		if (sub == NULL)
			return (NULL);
		tmp = end_text;
		end_text = ft_formatf("%s%s", end_text, sub);
		free_ptr((void **)&tmp);
		free_ptr((void **)&sub);
	}
	return (end_text);
}
