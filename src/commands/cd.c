/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:11 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/12 20:14:47 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"


#include "../header/mini_shell.h"


int	command_cd(t_)
{
	char	s[100];
	
	
	if(chdir(folder) == 0)
	{
	printf("%s\n", getcwd(s, 64));
		return(0);
	}
	else
	{
		printf("%s\n", strerror(errno));
		return(-1);	
	}
	return (0);
}
