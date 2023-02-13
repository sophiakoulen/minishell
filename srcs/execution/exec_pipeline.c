/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/13 15:26:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_pipeline(t_list *pipeline, t_env **env, int prev);

/*
	Execute the abstract-syntax tree corresponding to the line entered by
	the user.

	This is done recursively:
	If the current node is a leaf, that means it corresponds to a pipeline.
	We try to expand it then execute it.

	Else, we first execute the left child.
	Depending on the return value and whether the node of the
	tree is an && or an ||, we maybe execute the right child.

	If the right child was executed the return value is that of the
	right child, else it is that of the left child.
*/
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
	if (exec->n == 1 && exec->cmds[0].builtin != -1)
		ret = launch_builtin(exec, 0);
	else if (exec->n >= 1)
		ret = cmds_with_forks(exec);
	cleanup_exec(exec);
	free(exec);
	return (ret);
}
