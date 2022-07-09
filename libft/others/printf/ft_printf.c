/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:51:33 by llima-ce          #+#    #+#             */
/*   Updated: 2022/07/09 15:36:02 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_formated(t_format *buffer, char *formated)
{
	int		a;

	a = 0;
	while (a < buffer->len)
	{
		write(1, &formated[a], 1);
		a++;
	}
	free(formated);
	return (ft_end_struct(buffer));
}

int	ft_printf(const char *format, ...)
{
	t_format	*buffer;
	va_list		args;
	char		*formated;
	int			len;

	if (format == NULL)
		return (0);
	va_start(args, format);
	buffer = ft_start_struct(args);
	formated = ft_vformatf(format, buffer);
	len = put_formated(buffer, formated);
	va_end(args);
	return (len);
}
