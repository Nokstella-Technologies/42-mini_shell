/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:58:14 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/03 19:08:58 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verify_sign(char **str, int *err)
{
	while (**dest == ' ' || (**dest >= 9 && (**dest <= 13)))
		*dest++;
	sign = 1;
	if (**dest == '+' || **dest == '-')
	{
		if (**dest == '-')
			sign = -sign;
		*dest++;
	}
	return (a);
}

long long	ft_atol(char *str, int *err)
{
	long long	num;
	int			sign;

	sign = verify_sign(&str);
	num = 0;
	while (dest[a] <= '9' && dest[a] >= '0')
	{
		num *= 10;
		num = num + dest[a] - 48;
		a++;
	}
	return (num * sign);
}