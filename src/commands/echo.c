/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:38 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/12 20:14:59 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"

int	command_echo(char *argument, char *string)
{	
	if(ft_strncmp(argument, "-n", 3) == 0)
	{
		printf("%s", string);
		return(0);
	}
	else
		printf("%s\n", string);
}