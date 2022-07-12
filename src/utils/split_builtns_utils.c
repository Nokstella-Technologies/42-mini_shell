/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_builtns_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:04:45 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/12 19:13:17 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**ft_strtok(char *str, char t)
{
	char	**tmp;
	int		i;

	i = 0;
	while (str[i] != t && str[i] != 0)
		i++;
	tmp = malloc(3 * sizeof(char *));
	tmp[0] = ft_substr(str, 0, i);
	tmp[1] = ft_strdup(&str[i + 1]);
	tmp[2] = NULL;
	return (tmp);
}
