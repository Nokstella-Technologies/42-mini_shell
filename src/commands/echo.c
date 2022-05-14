/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:38 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/14 16:53:28 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"

void	command_echo(char *argument, char *string)
{	
	if(ft_strncmp(argument, "-n", 3) == 0)
	{
		printf("%s", string);
	}
	else
		printf("%s\n", string);
	
}