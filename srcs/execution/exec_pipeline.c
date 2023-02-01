/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/01 12:46:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Execute pipeline and return exit status of last command.
	Needs the environment to work with and send to child processes.
	If there is only one command, we don't fork.
*/
int	exec_pipeline(t_list *pipeline, t_env **env, int prev)
{
	t_exec	*exec;
	int		ret;

	exec = prepare_pipeline(pipeline, env, prev);
	ret = 0;
	if (exec->n == 1 && exec->cmds[0].builtin != -1)
	{
		ret = launch_builtin(exec, 0);
		printf("%d %d\n", ret, compute_return_value(ret));
	}
	else if (exec->n >= 1)
		ret = multiple_commands(exec);
	cleanup_exec(exec);
	free(exec);
	return (compute_return_value(ret));
}
