/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/07 23:20:32 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/libft.h"
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

# define BUFFER 256

typedef struct s_fds
{
	int	in_fd;
	int	out_fd;
	int	tmp_out;
	int	heredoc_fd;
	int	fd[2];
}		t_fds;

typedef struct s_cmd
{
	char	*line_cmd;
	char	*path_cmd;
	char	**argv;
}			t_cmd;

typedef struct s_ms
{
	int		*err;
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


int		testing_access(t_cmd *cmd);
int		find_cmd(t_cmd *cmd);
void	command_not_found(t_ms *ms);
int		dup_custom(int fd1, int fd2);
t_ms	*init_struct(char *line, int *err);
void	error_token(t_ms *ms);
void	free_all(t_ms **ms);
void	tokeneer(t_ms *ms, char *read, int a, char *s_tmp);
t_bool	mini_shell(int *err);
void	init_sigaction(t_sigaction *sa, void (*hd)(int), int sig);
void	handler_sig(int sig);
void	pwd(void);
void	ms_pipe(t_cmd **cmds, t_fds *fds);
void	exec_command(t_cmd *cmd, t_ms *ms);
void	command_cd(t_ms *ms);
void	command_echo(t_ms *ms);
void	command_env(t_cmd *cmd);
void	command_exit(t_ms *ms);
void	command_export(t_ms *ms);
void	command_pwd(t_ms *ms);
void	command_unset(t_cmd *cmd);
void	set_env(char *name, char *value);
void	end_program(t_ms **ms);
void	free_g_envp(void);
void	verify_next_move(t_ms *ms);
void	custom_close(int *fd);
void	custom_perror(t_ms *ms, int err, char *str);
void	exec_elf(t_cmd *cmd);
void	heredoc(t_ms *ms, t_cmd *eof);
char	*get_cwd(void);
char	*verify_text(char *text);
char	*verify_quotes(char *text, int i);
char	*verify_token(t_ms *ms, char *s_tmp, char a);
int		verify_error(char *handlers, int len, int err);
void	verify_cmd(t_ms *ms, char *str);
void	add_token(t_ms *ms, char *token);
void	pipe_exit(t_cmd *cmd, t_fds *fd, int fd_tmp, t_ms *ms);
void	history(char *r);
void	command_history(void);
char	**ft_strtok(char *str, char t);
char	*get_envp(char *var);
char	**create_envp(char **envp);


#endif