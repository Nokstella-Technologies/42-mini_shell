/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/14 20:24:18 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_fill_matrix(char const *s, size_t num, char **res);
static size_t	count_s(char const *s);

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
	return (res);
}

static int	verify_quotes(char const *s, size_t num)
{
	char quote;

	quote = *s;
	num++;
	while ((num == 1 || s[num] != quote) && s[num] != 0)
	{
		num++;
		if (s[num] == '\\' && s[num + 1] == quote)
			num += 2;
	}
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
		if (*(tmp) == '\''|| *(tmp) == '\"')
		{
			tmp += verify_quotes(tmp, 0);
			if (*(tmp) == ' ' || *(tmp) == 0)
				count++;
		}
		else
		{
			while (*tmp != ' ' && *tmp != 0)
				++tmp;
			if (*(tmp - 1) != ' ')
				count++;
		}
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
		while (*start_str == ' ' && *start_str != 0)
			++start_str;
		while (start_str[len_word] != ' ' && start_str[len_word] != 0)
		{
			if (start_str[len_word] == '\'' || start_str[len_word] == '\"' )
				len_word = verify_quotes(start_str, len_word);
			else if (start_str[len_word] == ' ' && start_str[len_word] == 0)
				break ;
			else
				len_word++;
		}
		res[count] = ft_substr(start_str, 0, len_word);
		start_str += len_word;
		count++;
	}
}