/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:12:04 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/22 00:21:07 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	find_second_quote(char *sub, char quote, char **tmp)
{
	int	i;

	i = 0;
	while (sub[i] && sub[i] != quote)
		i++;
	if (sub != &sub[i] && sub[i] == quote)
	{
		*tmp = ft_substr(sub, 0 , i);
		if (quote == '\"')
			*tmp = sub_env(NULL, *tmp);
		return (i + 2);
	}
	else
	{
		*tmp = NULL;
		return (i);
	}
}

static int	find_without_quote(char *sub, char **tmp)
{
	int	i;

	i = 0;
	while (sub[i] && sub[i] != '\"' && sub[i] != '\'')
		i++;
	*tmp = ft_substr(sub, 0 , i);
	*tmp = sub_env(NULL, *tmp);
	return (i);
}

char	*verify_quotes(char *text, int i)
{
	char	*sub;
	char	*end_text;
	char	*tmp;
	
	end_text = ft_strdup("");
	while (text[i] != 0)
	{
		if (text[i] == '\"' || text[i] ==  '\'')
			i += find_second_quote(text + i + 1, text[i], &sub);
		else
			i += find_without_quote(text + i, &sub);
		if (sub == NULL)
			return (NULL);
		tmp = end_text;
		end_text = ft_formatf("%s%s", end_text, sub);
		free_ptr((void **)&tmp);
		free_ptr((void **)&sub);
	}
	return(end_text);
} 

