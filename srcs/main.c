/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 18:12:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(void);

int	main(int argc, char **argv)
{
	ft_printf("test\n");
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
	t_tree	*tree;
	t_token	*tok_list;
	t_cmd	*cmds;
	int		n_cmds;

	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		tok_list = construct_tok_list(line);

		parse_commandline(&tree, tok_list);

		constuct_cmds(tree, &cmds, &n_cmds);

		exec_pipeline(cmds, n_cmds);

		// free cmds
		// free tree
		// free tok_list
		free(line);
	}
}
