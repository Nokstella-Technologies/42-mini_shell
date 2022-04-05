/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/05 18:15:34 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"

/*
echo -n
cd 
pwd
export
unset
env
exit
history
manusear single quotes
manusear double quotes com do $
executar ./
<<
>>
<
>
Ctrl D, Ctrl C, Ctrl \
**BONUS**
||
&&
Wildcard * working for the current dir
*/
char **g_envp;


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_envp = envp;
	while(1)
	{
		mini_shell();
	}
	return 0;
}
