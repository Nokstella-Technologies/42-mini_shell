/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/05/03 11:43:20 by llima-ce         ###   ########.fr       */
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


typedef struct s_ms
{
	char	*handlers; //p = pipe, h = heredoc, o = or, a = and, > = out, t = truncate, c = command, f = file.
	char	*line;
	t_cmd	**cmd;
	t_fds	fd;
	int		err;
}		t_ms;

extern char					**g_envp;

typedef struct sigaction t_sigaction;

void	parse_string(t_ms *ms, char *read, int a, char *s_tmp);
void	mini_shell(void);
void	init_sigaction(t_sigaction *sa, void (*hd)(int), int sig);
void	handler_sig(int sig);
void	pwd(void);
t_ms	*init_struct(char *line);
void	ms_pipe(t_cmd **cmds, t_fds *fds);
void	command_env(void);

#endif

/*
- readline ler fd1 const char de entrada
- rl_clear_history Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.
- rl_on_new_line Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
- rl_replace_line Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
- rl_redisplay Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
- add_history add a line to the history
getcwd
chdir
stat
lstat
fstat
access
unlink
opendir
readdir
closedir
strerror


https://www.youtube.com/watch?v=hartxUrXqQM
https://viewsourcecode.org/snaptoken/kilo/index.html
ioctl
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
*/

// ttyname -> return a pointer to the null terminated byte in the pathname fo the terminal device that is open in the current file descriptor. 
// ttyslot -> refers to an old model used by no systemV systems, in modern SystemV and SystemD, deprecable for us. 
// isatty -> return 1 if the current fd is pointing to a terminal, returns 0 if not
// printf
// malloc
// free
// write
// open
// read
// close
// fork
// wait
// waitpid
// wait3
// wait4
// execve
// dup
// dup2
// exit
// pipe

// getenv
// kill
// perror