/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:33:22 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/15 02:50:43 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void add_token(t_ms *ms, char *token)
{
	char *tmp;

	tmp = ms->handlers;
	ms->handlers = ft_formatf("%s%s", ms->handlers, token);
	free(tmp);
}

static char *verify_token(t_ms *ms, char *s_tmp, char a)
{
	if (*s_tmp == a)
	{
		if (*s_tmp == '|')
			add_token(ms, "o");
		else if (*s_tmp == '>')
			add_token(ms, "t");
		else if (*s_tmp == '<')
			add_token(ms, "h");
		return(s_tmp + 1);
	}
	else if (*s_tmp == '|' || *s_tmp == '>' || *s_tmp == '<' || *s_tmp == '&')
		ms->err = -2;
	if (a == '|')
		add_token(ms, "p");
	if (a == '>')
		add_token(ms, ">");
	if (a == '<')
		add_token(ms, "<");
	return (s_tmp);
}

static char	*ft_verify_handlers(t_ms *ms, char *s_tmp)
{
	if(*(s_tmp) == '\0')
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
	else if(*(s_tmp) == '&')
		ms->err = -2;
	return(s_tmp + 1);
}

static void verify_cmd(t_ms *ms, char *str) {
	int strlen;

	strlen = ft_strlen(ms->handlers);
	if (*str == 0)
		return ;
	else if (ft_strlen(ms->handlers) > 1 && ms->handlers[strlen - 1] != '>' && ms->handlers[strlen - 1] != '<' && ms->handlers[strlen - 1] != 't')
		add_token(ms, "c");
	else
		add_token(ms, "f");
}

int	verify_error(char *handlers, int len, int err)
{
	if (handlers[len - 1] != 'c' && handlers[len - 1] != 'f' && err == 0)
	{
		if (handlers[len - 1] == 'p' || handlers[len - 1] == 'a' || handlers[len - 1] == 'o' )
			return (1);
		return (-2);
	}
	return (err);
}

static char	*find_next_token(t_ms *ms, char *line)
{
	char	quote;

	while (*line != '&' && *line != '>' && *line != '<' && *line != '|' && *line != 0)
	{
		if (*line == '\"' || *line == '\'')
		{
			quote = *line;
			line++;
			while(*line != quote)
			{
				if(*line == '\0')
				{
					ms->err = -3;
					return(NULL);
				}
				line++;
			}
		}
		line++;
	}
	if(*line == 0)
		return(NULL);
	return(line);
}

void	tokeneer(t_ms *ms, char *read, int a, char *s_tmp)
{
	t_cmd	**tmp;
	char	*cmd;
	int		b;
	
	while(*read != 0)
	{
		s_tmp = find_next_token(ms, read);
		if (s_tmp == NULL)
			s_tmp = read + ft_strlen(read);
		tmp = (t_cmd **)malloc((a + 2)* sizeof(t_cmd *));
		tmp[a] = (t_cmd *)malloc(1 * sizeof(t_cmd));
		tmp[a + 1] = NULL;
		tmp[a]->line_cmd = ft_substr(read, 0, s_tmp - read);
		cmd = ft_strtrim(tmp[a]->line_cmd, " ");
		verify_cmd(ms, cmd);
		read = ft_verify_handlers(ms, s_tmp);
		if(ms->cmd != NULL)
		{
			b = 0;
			while(b < a)
			{
				tmp[b] = ms->cmd[b];
				b++;
			}
			free(ms->cmd);
		}
		if (!ft_strncmp(cmd, "", 2) && !(a == 0 && (*ms->handlers == '>' || *ms->handlers == '<' || *ms->handlers == 'h' || *ms->handlers == 't')))
		{
			ms->err = -2;
		}
		free(tmp[a]->line_cmd);
		tmp[a]->line_cmd = cmd;
		ms->cmd = tmp;
		a++;
	}
	ms->err = verify_error(ms->handlers, ft_strlen(ms->handlers), ms->err);
}








	
	/**
	 * | pipe -> contar quantos comandos e quantos pipes
	 * > redirect output to a file se não fd 1
	 * < infile fd 0
	 * << heredoc
	 * >> fazer a saída no append mode
	 * && AND Se o primeiro não existe ele da erro, se o primeiro e segundo existe ele roda os dois e se os dois não existem ele não roda nenhum. 
	 * || OR Se o primeiro existe ele não roda o próximo, caso não exista nehum dos 2 ele 
	 */
