/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:58:14 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/12 18:39:44 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	verify_sign(char **str, int *err)
// {
// 	while (**dest == ' ' || (**dest >= 9 && (**dest <= 13)))
// 		*dest++;
// 	sign = 1;
// 	if (**dest == '+' || **dest == '-')
// 	{
// 		if (**dest == '-')
// 			sign = -sign;
// 		*dest++;
// 	}
// 	return (a);
// }

// long long	ft_atol(char *str, int *err)
// {
// 	long long	num;
// 	int			sign;

// 	sign = verify_sign(&str);
// 	num = 0;
// 	while (dest[a] <= '9' && dest[a] >= '0')
// 	{
// 		num *= 10;
// 		num = num + dest[a] - 48;
// 		a++;
// 	}
// 	return (num * sign);
// }

long	ft_strtol(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
