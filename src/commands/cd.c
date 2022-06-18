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

void	command_cd(t_cmd *cmd)
{
	char	*formated;
	char	*env;

	if (!cmd->argv[1])
		cmd->argv[1] = getenv("HOME");
	else if (cmd->argv[2] != NULL)
		printf("%s\n", strerror(errno));
	if (!cmd->argv[1])
		return ;
	if (strchr(cmd->argv[1], '~'))
	{
		formated = ft_formatf("%s%s",getenv("HOME"), &cmd->argv[1][1]);
		free(cmd->argv[1]);
		cmd->argv[1] = formated;
	}
	if (chdir(cmd->argv[1]) != 0)
		printf("%s\n", strerror(errno));
	else
	{ 
		set_env("OLDPWD", getenv("PWD"));
		env = get_cwd();
		set_env("PWD", env);
		free(env);
	}
}
