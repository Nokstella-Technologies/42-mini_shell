/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/28 13:43:04 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/libft.h"
# include "pipe.h"
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>

# define WORKSPACE getenv("NAME") ? getenv("NAME") : getenv("WORKSPACE")
# define BUFFER 256

typedef struct s_ms
{
	int		err;
	char	*line;
	int		cmd_now;
	int		cmd_number;
	int		cmd_file_now;
	int		fd_origin[2];
	int		handlers_counter;
	char	*handlers;
	t_fds	fd;
	t_cmd	**cmd;
}			t_ms;

extern char					**g_envp;

typedef struct sigaction	t_sigaction;

t_ms	*init_struct(char *line);
void	error_token(t_ms *ms);
void	free_all(t_ms **ms);
void	tokeneer(t_ms *ms, char *read, int a, char *s_tmp);
void	mini_shell(void);
void	init_sigaction(t_sigaction *sa, void (*hd)(int), int sig);
void	handler_sig(int sig);
void	pwd(void);
void	ms_pipe(t_cmd **cmds, t_fds *fds);
void	exec_command(t_cmd *cmd, t_ms *ms);
void	command_cd(t_cmd *cmd);
void	command_echo(t_cmd *cmd);
void	command_env(t_cmd *cmd);
void	command_exit(t_ms *ms);
void	command_export(t_cmd *cmd);
void	command_pwd(t_cmd *cmd);
void	command_unset(t_cmd *cmd);
void	set_env(char *name, char *value);
void	end_program(t_ms **ms);
void	free_g_envp(void);
void	verify_next_move(t_ms *ms);
void	custom_close(int *fd);
void	exec_elf(t_cmd *cmd);
void	heredoc(t_ms *ms, t_cmd *eof);
char	*sub_env(char *text, char *tmp);
char	*get_cwd(void);
char	*verify_text(char *text);
char	*verify_quotes(char *text, int i);
char	*verify_token(t_ms *ms, char *s_tmp, char a);
int		verify_error(char *handlers, int len, int err);
void	verify_cmd(t_ms *ms, char *str);
void	add_token(t_ms *ms, char *token);
void	pipe_exit(t_cmd *cmd, t_fds *fd, int fd_tmp);

#endif