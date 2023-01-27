/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/27 15:56:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple_command(t_cmd *cmd, t_fds *fds, t_env **env, int prev);

/*
	Execute pipeline and return exit status of last command.
	Needs the environment to work with and send to child processes.
	If there is only one command, we don't fork.
*/
int	exec_pipeline(t_pipeline *p, t_env **env, int prev)
{
	t_fds	*fds;
	int		ret;

	fds = prepare_fds(p->n_cmds);
	if (p->n_cmds == 1)
		ret = simple_command(p->cmds, fds, env, prev);
	else
		ret = multiple_commands(p->cmds, fds, p->n_cmds, *env, prev);
	cleanup_fds(fds, p->n_cmds);
	return (ret);
}

static int	simple_command(t_cmd *cmd, t_fds *fds, t_env **env, int prev)
{
	int			*pids;
	t_cmd_info	*infos;
	int			ret;

	pids = NULL;
	infos = prepare_all_cmds(cmd, fds, 1, *env);
	read_all_heredocs(infos, 1);
	if (infos[0].builtin != -1)
		ret = launch_builtin(infos, fds, env, prev);
	else
		pids = launch_all(infos, fds, 1, *env, prev);
	write_all_heredocs(infos, fds->hd_pipes, 1);
	close_fds(fds, 1);
	if (infos[0].builtin == -1)
		waitpid(*pids, &ret, 0);
	free(pids);
	cleanup_all_info(infos, 1);
	return (compute_return_value(ret));
}
