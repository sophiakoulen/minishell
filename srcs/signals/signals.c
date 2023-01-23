/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:58:04 by znichola          #+#    #+#             */
/*   Updated: 2023/01/23 17:54:59 by znichola         ###   ########.fr       */
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

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, &"\n", 1);
		rl_on_new_line();
		// rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

void	setup_sigaction(void)
{
	struct sigaction	ignore;
	struct sigaction	action;

	action.sa_handler = &handler;
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&action.sa_mask);
	sigemptyset(&ignore.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &ignore, NULL);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int	i;
// 	char	*line;

// 	setup_sigaction();

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
