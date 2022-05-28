/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an7onie77i <an7onie77i@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/28 17:59:44 by an7onie77i       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_fill_matrix(char const *s, size_t num, char **res);
static size_t	count_s(char const *s);


void remove_quote(char **res)
{
	int i;
	char *tmp;

	i = 0;
	while (res[i] != NULL)
	{
		if (res[i][0] == '\"')
		{
			tmp = res[i];
			res[i] = ft_substr(res[i], 1, ft_strlen(res[i]) - 2);
			free(tmp);
		}
		i++;
	}
}

char	**ft_split_pipe(char const *s)
{
	char	**res;
	size_t	num;

	res = NULL;
	if (!s)
		return (NULL);
	num = count_s(s);
	res = (char **)malloc(sizeof(char *) * (num + 1));
	if (!res)
		return (NULL);
	res[num] = NULL;
	ft_fill_matrix(s, num, res);
	remove_quote(res);
	return (res);
}

static int	verify_quotes(char const *s, size_t num)
{
	char quote;

	quote = s[num];
	num++;
	while ((num == 1 || s[num] != quote) && s[num] != 0)
	{
		if(s[num] == '\\' && s[num + 1] == '\"')
			num += 2;
		num++;
	}
	if(s[num] != 0)
		num++;
	return (num);
}

static size_t	count_s(char const *s)
{
	size_t		count;
	char		*tmp;

	tmp = (char *)s;
	count = 0;
	while (*tmp != 0)
	{
		while (*tmp == ' ' && *tmp != 0)
			++tmp;
		while (*tmp != ' ' && *tmp != 0)
		{
			if (*(tmp) == '\''|| *(tmp) == '\"')
			{
				tmp += verify_quotes(tmp, 0);
				if (*(tmp) == ' ' || *(tmp) == 0)
					count++;
			}
			else 
				++tmp;
		}
		if (*(tmp - 1) != ' ')
			count++;
	}
	return (count);
}

static void	ft_fill_matrix(char const *s, size_t num, char **res)
{
	size_t	count;
	char	*start_str;
	int		len_word;

	count = 0;
	start_str = (char *)s;
	while (count < num)
	{
		len_word = 0;
		while (*start_str != 0 && *start_str == ' ')
			++start_str;
		while (start_str[len_word] != 0 && start_str[len_word] != ' ')
		{
			if (start_str[len_word] == '\'' || start_str[len_word] == '\"' )
				len_word = verify_quotes(start_str, len_word);
			else if (start_str[len_word] == 0 && start_str[len_word] == ' ')
				break ;
			else
				len_word++;
		}
		res[count] = ft_substr(start_str, 0, len_word);
		start_str += len_word;
		count++;
	}
}