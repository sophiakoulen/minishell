/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 12:29:06 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(void);

/*
	alternative method to find the env variable
	can also use this way
	extern char	**environ;
 */

// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv, char **envp)
{
	t_env *env = init_env(envp);
	// print_env(env, NULL);
	// env_to_strarr(env);
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
	t_token	*tok_list;

	while (1)
	{
		line = readline("minishell\033[38:5:117m$ \033[0m");
		// line = readline("minishell$ ");
		if (line && *line)
			add_history(line);

		tok_list = construct_tok_list(line);
		t_token *start = tok_list;

		t_pipeline *p = x_malloc(sizeof(*p), 1);

		parse_pipeline(p, &tok_list);

		exec_pipeline(p);

		pipeline_cleanup(p);
		free(p);

		tok_list_cleanup(start);

		free(line);
	}
}
