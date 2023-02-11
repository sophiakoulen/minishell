/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/11 13:08:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_pipeline(t_list *pipeline, t_env **env, int prev);

int	exec_tree(t_tree *tree, t_env **env, int prev)
{
	int	ret;

	if (!tree)
		return (0);
	if (!tree->left && !tree->right)
	{
		if (expand_pipeline(&tree->pipeline, *env, prev) != 0)
			return (1);
		return (exec_pipeline(tree->pipeline, env, prev));
	}
	ret = exec_tree(tree->left, env, prev);
	if (!!ret == (tree->type == e_or))
		ret = exec_tree(tree->right, env, prev);
	return (ret);
}

/*
	Execute pipeline and return exit status of last command.
	Needs the environment to work with and send to child processes.
	If there is only one command, we don't fork.
*/
static int	exec_pipeline(t_list *pipeline, t_env **env, int prev)
{
	t_exec	*exec;
	int		ret;

	exec = prepare_pipeline(pipeline, env, prev);
	ret = 0;
	silent_signals();
	get_set_termios(0);
	if (exec->n == 1 && exec->cmds[0].builtin != -1)
		ret = launch_builtin(exec, 0);
	else if (exec->n >= 1)
		ret = multiple_commands(exec);
	cleanup_exec(exec);
	free(exec);
	get_set_termios(1);
	parent_signals();
	return (ret);
}
