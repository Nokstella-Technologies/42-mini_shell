/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:33:22 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/10 17:47:14 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*ft_verify_handlers(t_ms *ms, char *s_tmp)
{
	if (*(s_tmp) == '\0')
		return (s_tmp);
	else if (*(s_tmp) == '>')
		return (verify_token(ms, s_tmp + 1, '>'));
	else if (*(s_tmp) == '<')
		return (verify_token(ms, s_tmp + 1, '<'));
	else if (*(s_tmp) == '|')
		return (verify_token(ms, s_tmp + 1, '|'));
	else if (*(s_tmp) == '&' && *(s_tmp + 1) == '&')
	{
		add_token(ms, "a");
		return (s_tmp + 2);
	}
	else if (*(s_tmp) == '&')
		ms->err[0] = -2;
	return (s_tmp + 1);
}

static char	*find_next_token(t_ms *ms, char *line)
{
	char	quote;
	int		a;

	a = 0;
	while (line[a] != '&' && line[a] != '>'
		&& line[a] != '<' && line[a] != '|' && line[a] != 0)
	{
		if (line[a] == '\"' || line[a] == '\'')
		{
			quote = line[a];
			line++;
			while (line[a] != quote)
			{
				if (line[a] == '\0')
				{
					ms->err[0] = -3;
					return (NULL);
				}
				a++;
			}
		}
		a++;
	}
	if (line[a] == 0)
		return (NULL);
	return (&line[a]);
}

static t_cmd	**struct_value_to_tokeneer(t_ms *ms, int a, t_cmd **tmp)
{
	int	b;

	if (ms->cmd != NULL)
	{
		if (tmp[a]->line_cmd[0] == '\0')
		{
			free_ptr((void **) &tmp[a]->line_cmd);
			free_ptr((void **) &tmp);
			return (NULL);
		}
		b = 0;
		while (b < a)
		{
			tmp[b] = ms->cmd[b];
			b++;
		}
		free(ms->cmd);
	}
	else if (tmp[a]->line_cmd[0] == '\0')
	{
		free_ptr((void **) &tmp[a]->line_cmd);
		free_ptr((void **) &tmp);
		return (NULL);
	}
	return (tmp);
}

void	tokeneer_if(t_ms *ms, int a)
{
	if (ms->cmd != NULL && !ft_strncmp(ms->cmd[a]->line_cmd, "", 2) 
		&& !(a == 0 && (*ms->handlers == '>'|| *ms->handlers == '<'
		|| *ms->handlers == 'h' || *ms->handlers == 't')))
		ms->err[0] = -2;
}

void	tokeneer(t_ms *ms, char *read, int a, char *s_tmp)
{
	t_cmd	**tmp;
	char	*cmd;

	while (*read != 0)
	{
		s_tmp = find_next_token(ms, read);
		tmp = (t_cmd **)malloc((a + 2) * sizeof(t_cmd *));
		if (s_tmp == NULL)
			s_tmp = ft_strchr(read, '\0');
		tmp[a] = (t_cmd *)malloc(1 * sizeof(t_cmd));
		tmp[a + 1] = NULL;
		tmp[a]->line_cmd = ft_substr(read, 0, s_tmp - read);
		tmp[a]->path_cmd = NULL;
		tmp[a]->argv = NULL;
		cmd = ft_strtrim(tmp[a]->line_cmd, " ");
		verify_cmd(ms, cmd);
		free(tmp[a]->line_cmd);
		tmp[a]->line_cmd = cmd;
		tmp = struct_value_to_tokeneer(ms, a, tmp);
		read = ft_verify_handlers(ms, s_tmp);
		tokeneer_if(ms, a);
		ms->cmd = tmp;
		a++;
	}
	ms->err[0] = verify_error(ms->handlers, ft_strlen(ms->handlers),ms->err[0]);
}
