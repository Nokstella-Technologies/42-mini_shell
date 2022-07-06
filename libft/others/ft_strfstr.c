/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:02:08 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/06 00:30:05 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfstr(const char *str, const char *ptr)
{
	int	a;

	a = 0;
	if (str == NULL || ptr == NULL)
		return (NULL);
	while (str[a] && !ft_strchr(ptr, str[a]))
		a++;
	if (str[a] == 0)
		return (NULL);
	return ((char *)str + a);
}
