/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 10:40:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple_command(t_exec *exec);

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
	if (exec->n == 1)
		ret = simple_command(exec);
	else
	{
		ret = multiple_commands(exec);
	}
	cleanup_exec(exec);
	free(exec);
	return (ret);
}

static int	simple_command(t_exec *exec)
{
	int			*pids;
	int			ret;

	pids = NULL;
	read_all_heredocs(exec);
	if (exec->cmds[0].builtin != -1)
		ret = launch_builtin(exec, 0);
	else
		pids = launch_all(exec);
	write_all_heredocs(exec);
	close_fds(exec);
	if (exec->cmds[0].builtin == -1)
		waitpid(*pids, &ret, 0);
	free(pids);
	return (compute_return_value(ret));
}
