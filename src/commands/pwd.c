/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:42 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/21 15:26:28 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	command_pwd(t_cmd *cmd)
{
	char	*path;

	(void) cmd;
	path = get_cwd();
	printf("%s\n", path);
	free(path);
}
