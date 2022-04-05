/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <luizlcezario@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/04/05 18:57:49 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/libft.h"

typedef struct s_cmd
{
	char	*path_cmd;
	char	**argv;
}			t_cmd;

typedef struct s_ms
{
	char *line;
	t_cmd **cmd;
}		t_ms;

extern char					**g_enpv;

typedef struct sigaction t_sigaction;

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
#  include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>


void mini_shell(void);

#endif

/*
readline ler fd1 const char de entrada
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
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
isatty
ioctl


ttyslot
ttyname
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
*/

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