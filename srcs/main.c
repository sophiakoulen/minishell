/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 22:35:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(t_env *env);
static int	exec_line(char *line, t_env *env);

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = init_env(envp);
	check_args(argc, argv);
	interactive_shell(env);
	return (0);
}

static void	check_args(int argc, char **argv)
{
	const char	*msg1;
	const char	*msg2;

	(void)argv;
	msg1 = "Script files are currently not supported.\n";
	msg2 = "Use ./minishell to start an interactive shell.\n";
	if (argc != 1)
	{
		write(2, msg1, ft_strlen(msg1));
		write(2, msg2, ft_strlen(msg2));
		exit(2);
	}
}

static void	interactive_shell(t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		exec_line(line, env);
		free(line);
	}
}

static int	exec_line(char *line, t_env *env)
{
	int					ret;
	t_token				*tok_list;
	t_token				*start;
	t_parsed_pipeline	*parsed;
	t_pipeline			*pipeline;

	ret = 0;
	tok_list = construct_tok_list(line);
	start = tok_list;
	if (start->type != e_end)
	{
		parsed = x_malloc(sizeof(*parsed), 1);
		if (parse_pipeline(parsed, &tok_list) == SUCCESS)
		{
			pipeline = expand_pipeline(parsed);
			ret = exec_pipeline(pipeline, env);
			pipeline_cleanup(pipeline);
			free(pipeline);
		}
		else
			ret = 2;
		parsed_pipeline_cleanup(parsed);
	}
	tok_list_cleanup(start);
	return (ret);
}
