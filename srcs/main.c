/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 17:22:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(t_env *env);

/*
	alternative method to find the env variable
	can also use this way
	extern char	**environ;
 */

// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv, char **envp)
{
	t_env *env;

	env = init_env(envp);

	check_args(argc, argv);

	interactive_shell(env);
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

static void	interactive_shell(t_env *env)
{
	char		*line;
	t_token		*tok_list;
	t_token		*start;
	t_pipeline	*p;

	(void)env;
	while (1)
	{
		line = readline("minishell\033[38:5:117m$ \033[0m");
		// line = readline("minishell$ ");
		if (line && *line)
			add_history(line);

		tok_list = construct_tok_list(line);
		start = tok_list;

		if (start->type != e_end)
		{
			p = x_malloc(sizeof(*p), 1);

			parse_pipeline(p, &tok_list);

			exec_pipeline(p);

			pipeline_cleanup(p);
			free(p);
		}

		tok_list_cleanup(start);

		free(line);
	}
}
