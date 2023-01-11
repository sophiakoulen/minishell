/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/01/11 16:25:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(void);

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	interactive_shell();
	return (0);
}

static void	check_args(int argc, char **argv)
{
	const char	*msg;

	(void)argv;
	msg = "Script files are currently not supported.\nUse ./minishell to start an interactive shell.\n";
	if (argc != 1)
	{
		write(2, msg, ft_strlen(msg));
		exit(1);
	}
}

static void	interactive_shell(void)
{
	char	*line;
	
	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		free(line);
	}
}
