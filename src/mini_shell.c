/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:28:24 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/05 18:14:35 by llima-ce         ###   ########.fr       */
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
	char *r;
	
	printf("%s@%s:%s$ ", getenv("LOGNAME"), getenv("NAME"), getcwd(s, 100));
	r = readline(NULL);
	if (!ft_strncmp(r, "pwd", 3))
		pwd();
	// else if (!ft_strncmp(r, "exit", 4))
	free(r);
}
