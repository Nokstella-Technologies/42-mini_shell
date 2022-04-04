/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:30 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/04 16:01:34 by vantonie         ###   ########.fr       */
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

void	pwd()
{
	char s[200];

	printf("%s\n", getcwd(s, 200));
}


int	main()
{
	char s[100];
	char *r;
	
	sigaction();
	signal();
	while(1)
	{
		printf("%s@%s:%s$ ", getenv("LOGNAME"), getenv("NAME"), getcwd(s, 100));
		r = readline(NULL);
		if (!ft_strncmp(r, "pwd", 3))
			pwd();
		else if (!ft_strncmp(r, "exit", 4))
			sigaddset();
		free(r);
	}

	return 0;
}