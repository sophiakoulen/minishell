/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:29 by znichola          #+#    #+#             */
/*   Updated: 2023/02/16 13:32:11 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv);
static void	interactive_shell(t_env **env, int *retn);
static int	exec_line(char *line, t_env **env, int *retn);

int		g_retn = 0;

int	main(int argc, char **argv, char **envp)
{
	static t_env		*env[1];

	// env = (t_env **)x_malloc(sizeof(t_env *), 1);
	if (isatty(0) && isatty(2))
		rl_outstream = stderr;
	get_set_termios(1);
	parent_signals();
	*env = init_env(envp);
	check_args(argc, argv);
	interactive_shell(env, &g_retn); //why are we giving it a pointer if it's a global????????
	rl_clear_history();
	env_cleanup_all(*env);
	// free(env);
	exit(g_retn);
	return (g_retn);
}

static void	check_args(int argc, char **argv)
{
	int	fd;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			print_error(0, argv[1], strerror(errno));
			if (errno == ENOENT)
				exit(127);
			else
				exit(126);
		}
		dup2(fd, 0);
		close(fd);
	}
}

static char	*read_input(int retn)
{
	if (isatty(0) && isatty(2))
	{
		if (!retn)
			return (readline(BLUE_PROMPT));
		else
			return (readline(RED_PROMPT));
	}
	else
		return (get_next_line(0));
}

/*
	I removed the hack with write to change the line we are writing on,
	because it caused problems in non-interactive mode.
*/
static void	interactive_shell(t_env **env, int *retn)
{
	char	*line;
	int		need_to_exit;

	need_to_exit = 0;
	while (!need_to_exit)
	{
		line = read_input(*retn);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		silent_signals();
		get_set_termios(0);
		exec_line(line, env, retn);
		if (*ret_env_key(*env, "EXIT"))
			need_to_exit = 1;
		get_set_termios(1);
		parent_signals();
		free(line);
	}
	if (isatty(0) && isatty(2))
		write(2, "exit\n", 5);
	get_set_termios(0);
}

static int	exec_line(char *line, t_env **env, int *retn)
{
	t_token	*tok_list;
	t_token	*start;
	t_tree	*tree;

	if (construct_tok_list(&tok_list, line) != 0)
	{
		*retn = 258;
		return (*retn);
	}
	start = tok_list;
	if (parse_tree(&tree, &tok_list) != SYNTAX_ERROR)
	{
		*retn = exec_tree(tree, env, *retn);
		pipe_return_print(*retn);
	}
	else
		*retn = 258;
	tree_cleanup(tree);
	tok_list_cleanup(start);
	return (*retn);
}
