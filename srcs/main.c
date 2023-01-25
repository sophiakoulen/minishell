/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/01/25 15:43:56 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(t_env *env, int *retn);
static int	exec_line(char *line, t_env **env, int *retn);

int	g_retn = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	// static int	retn;

	get_set_termios(1);
	parent_signals();
	env = init_env(envp);
	check_args(argc, argv);
	interactive_shell(env, &g_retn);
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

static void	interactive_shell(t_env *env, int *retn)
{
	char	*line;

	while (1)
	{
		if (*retn == 0)
			line = readline("minishell\001\033[38:5:117m\002$\001\033[0m\002 ");
		else
			line = readline("minishell\001\033[38:5:197m\002$\001\033[0m\002 ");
		if (!line)
		{
			exec_exit(NULL, &env, *retn);
			break ;
		}
		if (*line)
			add_history(line);
		get_set_termios(0);
		exec_line(line, &env, retn);
		get_set_termios(1);
		parent_signals();
		free(line);
	}
}

static int	exec_line(char *line, t_env **env, int *retn)
{
	// static int			ret = 0;
	t_token				*tok_list;
	t_token				*start;
	t_parsed_pipeline	*parsed;
	t_pipeline			*pipeline;

	if (construct_tok_list(&tok_list, line) != 0)
	{
		*retn = 258;
		return (*retn);
	}
	start = tok_list;
	if (start->type != e_end)
	{
		parsed = x_malloc(sizeof(*parsed), 1);
		if (parse_pipeline(parsed, &tok_list) == SUCCESS)
		{
			if (expand_pipeline(&pipeline, parsed, *env, *retn) == 0)
			{
				silent_signals();
				*retn = exec_pipeline(pipeline, env, *retn);
				pipe_return_print(*retn);
				pipeline_cleanup(pipeline); //need to free list of args and list of redirs
				free(pipeline);
			}
			else
				*retn = 1;
			parsed_pipeline_cleanup(parsed); //need to free cmd and the items
		}
		else
			*retn = 258;
	}
	tok_list_cleanup(start);
	return (*retn);
}
