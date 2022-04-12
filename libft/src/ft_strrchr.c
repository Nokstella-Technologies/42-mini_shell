/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:03:27 by llima-ce          #+#    #+#             */
/*   Updated: 2022/04/12 19:06:14 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int n)
{
	char	*tmp;
	int		num;

	tmp = (char *) str;
	num = ft_strlen(str);
	while (*(tmp + num) != (char)n)
	{
		if (num == 0)
			return (NULL);
		num--;
	}
	return ((char *)(tmp + num));
}
