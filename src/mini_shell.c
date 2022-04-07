/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/06 18:50:19 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"



void mini_shell(void)
{
	char s[100];
	char *prompt;
	char *r;

	r = ft_strdup("");
	while(r != NULL)
	{
		if (r)
			free_ptr((void **)&r);
		getcwd(s, 100);
		prompt = ft_formatf("%s@%s:%s$ ", getenv("LOGNAME"), WORKSPACE, s);
		r = readline(prompt);
		free(prompt);
		if (!r)
			printf("\n");
		else if (!ft_strncmp(r, "pwd", 3))
			pwd();
		else if (!ft_strncmp(r, "exit", 4))
			exit(0);
		else
			printf("ok vamos tentar %s\n", r);
	}
	exit(0);
}
