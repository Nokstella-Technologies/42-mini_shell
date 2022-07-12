/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:40 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/12 17:08:48 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*verify_text(char *text)
{
	char	*tmp2;

	tmp2 = verify_quotes(text, 0);
	if (tmp2 == NULL)
		return (NULL);
	return (tmp2);
}

static char	*concat_all(char **splitted)
{
	char	*tmp;
	char 	*final;
	int		a;

	a = 1;
	final = ft_strdup("");
	while(splitted[a] != NULL)
	{
		tmp = final;
		final = ft_formatf("%s%s", final, splitted[a]);
		free_ptr((void **)&tmp);
		a++;
	}
	return (final);
}

void	verify_err(t_ms *ms, int i)
{
	int	a;

	a = 0;
	while (ft_isdigit(ms->cmd[ms->cmd_now]->argv[i][a]) != 0)
		a++;
	if (ms->cmd[ms->cmd_now]->argv[i][a] == 0)
		custom_perror(ms->err, 1, "not a valid identifier", "export");
	else {
		a = 0;
		while (ft_isalpha(ms->cmd[ms->cmd_now]->argv[i][a]) != 0)
			a++;
		if (ms->cmd[ms->cmd_now]->argv[i][a] != 0 )
			custom_perror(ms->err, 1, "not a valid identifier", "export");
	}
}

static void	export(t_ms *ms, int i, char **splitted)
{
	char	*tmp;
	int		a;

	if (ft_strchr(ms->cmd[ms->cmd_now]->argv[i], '=') != NULL)
	{
		a = 0;
		while (splitted[0] != NULL && ft_isalpha(splitted[0][a]) != 0)
			a++;
		if (splitted[0] == NULL || splitted[0][a] != 0 )
			custom_perror(ms->err, 1, "not a valid identifier", "export");
		else if (ft_strchr(ms->cmd[ms->cmd_now]->argv[i], '=') == ms->cmd
			[ms->cmd_now]->argv[i] || ft_strchr(splitted[0], ' ') != NULL)
			custom_perror(ms->err, 1," =': not a valid identifier", "export");
		else if (splitted[1] == NULL)
			set_env(splitted[0], "");
		else
		{
			tmp = concat_all(splitted);
			set_env(splitted[0], tmp);
			free_ptr((void **)&tmp);
		}
	}
	else
		verify_err(ms, i);
}

void	command_export(t_ms *ms)
{
	char	**splitted;
	int		i;

	i = 1;
	// free_ptr((void **) &ms->cmd[ms->cmd_now]->argv[1]);
	// free_ptr((void **) &ms->cmd[ms->cmd_now]->argv[0]);
	// free_ptr((void **) &ms->cmd[ms->cmd_now]->argv);
	// ms->cmd[ms->cmd_now]->argv = ft_split_pipe( ms->cmd[ms->cmd_now]->line_cmd);
	while (ms->cmd[ms->cmd_now]->argv[i] != NULL)
	{
		splitted = ft_split(ms->cmd[ms->cmd_now]->argv[i], '=');
		export(ms, i, splitted);
		free_ptr((void **)&splitted[0]);
		free_ptr((void **)&splitted[1]);
		free_ptr((void **)&splitted);
		i++;
	}
}
