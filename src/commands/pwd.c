/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:42 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/07 19:17:49 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	command_pwd(t_ms *ms)
{
	char	*path;

	(void ) ms;
	path = get_cwd();
	printf("%s\n", path);
	free(path);
}
