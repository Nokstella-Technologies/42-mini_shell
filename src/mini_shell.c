/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/05 21:38:21 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

void	pwd()
{
	char s[200];

	printf("%s\n", getcwd(s, 200));
}

void mini_shell(void)
{
	char s[100];
	char *prompt;
	char *r;
	
	while(!r)
	{
		getcwd(s, 100);
		prompt = ft_formatf("%s@%s:%s$ ", getenv("LOGNAME"), WORKSPACE, s);
		r = readline(prompt);
		free(prompt);
		if (r == NULL)
			printf("\n");
		else if (!ft_strncmp(r, "pwd", 3))
		{
			pwd();
			free(r);
		}
		else if (!ft_strncmp(r, "exit", 4))
			exit(0);
		else
		{
			printf("ok vamos tentar %s", r);
			free(r);
		}
	}
	exit(0);
}
