/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:58:04 by znichola          #+#    #+#             */
/*   Updated: 2023/01/25 15:42:33 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// needed for wsl linux
// #define _XOPEN_SOURCE 700

#include "minishell.h"

// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <signal.h>
// # include <readline/readline.h>
// # include <readline/history.h>

/*
	SIGINT	ctrl-C	displays a new prompt on a new line.
			ctrl-D	exits the shell. not a signal but
						readline interprets it as EOF on an
						empty line this will exit the shell
	SIGQUIT	ctrl-\	does nothing
 */

extern int	g_retn;

/*
	The handeller for sig int. starts a new line leaving the old text inplace.
	TODO: to adjust the retn to be 1
 */
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_retn = 1;
		write(1, &"\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

/*
	A silent signal used for the handeller for minishell when it's
	exicuting a pipeline, no response is expected.
 */
void	silent_signal(int sig)
{
	if (sig == SIGQUIT)
	{
	}
	if (sig == SIGINT)
	{
	}
}

/*
	This behaviour is expeced by the consignes and how the program
	./minishell is to react.
 */
void	parent_signals(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_int.sa_handler = &sigint_handler;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

/*
	These signals are for the ./minishell when it's exituting a pipeline
	it ensures no signals are cought and nothing is printed.

	IMPORTANT:
	We can't use SIG_ING because this is inherited by a execve process!
 */
void	silent_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &silent_signal;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = &silent_signal;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	pipe_return_print(int retn)
{
	if (retn == 131)
		write(1, &"Quit: 3\n", 10);
	if (retn == 130)
		write(1, &"\n", 1);
}
