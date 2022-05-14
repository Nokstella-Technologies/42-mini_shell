/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:49:11 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/12 21:15:5 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mini_shell.h"
#include "../header/mini_shell.h"

void	command_cd(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) != 0)
		printf("%s\n", strerror(errno));
}
