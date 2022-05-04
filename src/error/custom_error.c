/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:08:12 by llima-ce          #+#    #+#             */
/*   Updated: 2022/05/03 11:15:56 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	custom_perror(t_ms *ms, int err, char *str)
{

}


static void error_t_aux(char now, char next)
{
	
}

void	error_token(t_ms *ms)
{
	int	a;
	int	cond;

	a = 0;
	while (ms->handlers[a] != 0)
	{
		if (a == 0 && (ms->handlers[a] == '|' || ms->handlers[a] == 'o'
			|| ms->handlers[a] == 'a'))
			custom_perror(ms, -2, ms->handlers[a]);
		else if (ms->handlers[a] == '|' || ms->handlers[a] == 'o' 
			|| ms->handlers[a] == 'a' || ms->handlers[a] == '>' 
			|| ms->handlers[a] == '<' || ms->handlers[a] == 't' 
			|| ms->handlers[a] == 'h')
		{
			if (ms->handlers[a + 1] == '|' || ms->handlers[a + 1] == 'o' 
			|| ms->handlers[a + 1] == 'a' || ms->handlers[a + 1] == '>' 
			|| ms->handlers[a + 1] == '<' || ms->handlers[a + 1] == 't' 
			|| ms->handlers[a + 1] == 'h')
				custom_perror(ms, -2, ms->handlers[a + 1]);
		}
		
		a++;
	}
}