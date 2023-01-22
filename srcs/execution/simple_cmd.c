/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:10:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/22 11:27:08 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_command(t_cmd *cmd, t_fds *fds, t_env **env)
{
	int			*pids;
	t_cmd_info	*infos;
	int			ret;

	pids = NULL;
	infos = prepare_all_cmds(cmd, fds, 1, *env);
	if (infos[0].builtin != -1)
		ret = launch_builtin(cmd, infos, fds, env);
	else
		pids = launch_all(cmd, infos, fds, 1, *env);
	do_all_heredocs(infos, fds->hd_pipes, 1);
	close_fds(fds, 1);
	if (infos[0].builtin == -1)
		waitpid(*pids, &ret, 0);
	free(pids);
	cleanup_all_info(infos, 1);
	return (compute_return_value(ret));
}
