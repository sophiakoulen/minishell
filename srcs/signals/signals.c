/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:58:04 by znichola          #+#    #+#             */
/*   Updated: 2023/01/25 13:22:16 by znichola         ###   ########.fr       */
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

// SIGINT	ctrl-C	displays a new prompt on a new line.
// 			ctrl-D	exits the shell. not a signal but readline interprets it as EOF on an empty line this will exit the shell
// SIGQUIT	ctrl-\	does nothing

extern int	g_child_pid;

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_child_pid)
		{
			ft_printf("\n\nin a child!\n\n");
			return ;
		}
		write(1, &"\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

void	silent_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_child_pid != 0)
		{
			write(1, &"int int child\n", 15);
			return ;
		}
		// write(1, &"^C\n", 4);
		// write(1, &"\n", 1);
		// rl_on_new_line();
		// rl_replace_line("\0", 0);
		// rl_redisplay();
	}
}


void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		// if (g_child_pid)
		// {
			// ft_printf("\n\nin a child!\n\n");
			// write(1, &"\n", 1);
			// rl_redisplay();
		if (g_child_pid != 0)
		{
			write(1, &"Quit: 3\n", 10);
			kill(g_child_pid, SIGQUIT);
		}
		else
		{
			write(1, &"Quit: 3\n", 10);
			// write(1, &"not in child\n", 14);
		}
		// }
		// rl_on_new_line();
		// rl_replace_line("\0", 0);
		// rl_redisplay();
	}
}

void	silent_sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		// if (g_child_pid)
		// {
			// ft_printf("\n\nin a child!\n\n");
			// write(1, &"\n", 1);
			// rl_redisplay();
		if (g_child_pid != 0)
		{
			write(1, &"Quit: 3\n", 10);
			kill(g_child_pid, SIGQUIT);
		}
		// else
		// {
		// 	write(1, &"Quit: 3\n", 10);
		// 	// write(1, &"not in child\n", 14);
		// }
		// }
		// rl_on_new_line();
		// rl_replace_line("\0", 0);
		// rl_redisplay();
	}
}

void	parent_signals(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_int.sa_handler = &sigint_handler;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART; // | SA_NOCLDWAIT;
	sigaction(SIGINT, &sig_int, NULL);

	// sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_handler = SIG_IGN;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART; // | SA_NOCLDWAIT;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	silent_signals(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &silent_sigint_handler;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART; // | SA_NOCLDWAIT;
	sigaction(SIGINT, &sig_int, NULL);


	// sig_quit.sa_handler = &sigquit_handler;
	// sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_handler = &silent_sigquit_handler;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART; // | SA_NOCLDWAIT;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

// void	silent_signals(void)
// {
// 	struct sigaction	sig_quit;
// 	struct sigaction	sig_int;

// 	sig_int.sa_handler = &silent_sigint_handler;
// 	sigemptyset(&sig_int.sa_mask);
// 	sig_int.sa_flags = SA_RESTART; // | SA_NOCLDWAIT;
// 	sig_quit.sa_handler = &sigquit_handler;
// 	sigaction(SIGINT, &sig_int, NULL);
// 	sigaction(SIGQUIT, &sig_quit, NULL);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int	i;
// 	char	*line;

// 	parent_signals();

// 	while (1)
// 	{
// 		// line = readline("\x01\033[34m\x02 prompte >  \x01\033[0m\x02");
// 		line = readline("prompte > ");
// 		if (!line)
// 			break ;
// 		if (*line)
// 			add_history(line);
// 		printf("you wrote %s\n", line);
// 		sleep(10);
// 		free(line);
// 	}
// 	return (0);
// }
