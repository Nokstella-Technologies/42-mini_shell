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

static void	change_home(t_ms *ms)
{
	char	**tmp;

	tmp = (char	**)malloc(3 * sizeof(char *));
	tmp[0] = ms->cmd[ms->cmd_now]->argv[0];
	tmp[1] = ft_strdup(getenv("HOME"));
	tmp[2] = NULL;
	free_ptr((void **) &ms->cmd[ms->cmd_now]->argv);
	ms->cmd[ms->cmd_now]->argv = tmp;
}

void	command_cd(t_ms *ms)
{
	char	*formated;
	char	*env;

	if (!ms->cmd[ms->cmd_now]->argv[1])
		change_home(ms);
	else if (ms->cmd[ms->cmd_now]->argv[2] != NULL)
		custom_perror(ms->err, 1, "too many arguments", "cd");
	else if (!ms->cmd[ms->cmd_now]->argv[1])
		return ;
	else if (strchr(ms->cmd[ms->cmd_now]->argv[1], '~'))
	{
		formated = ft_formatf("%s%s", getenv("HOME"),
				&ms->cmd[ms->cmd_now]->argv[1][1]);
		free(ms->cmd[ms->cmd_now]->argv[1]);
		ms->cmd[ms->cmd_now]->argv[1] = formated;
	}
	if (chdir(ms->cmd[ms->cmd_now]->argv[1]) != 0)
		custom_perror(ms->err, 1, "No such file or directory", "cd");
	else
	{
		set_env("OLDPWD", getenv("PWD"));
		env = get_cwd();
		set_env("PWD", env);
		free(env);
	}
}
