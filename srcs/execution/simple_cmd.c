/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:10:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 11:54:48 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_builtin(t_cmd *cmds, t_cmd_info *infos, t_fds *fds);

int	simple_command(t_cmd *cmd, t_fds *fds)
{
	int			*pids;
	t_cmd_info	*infos;
	int			ret;

	pids = NULL;
	infos = prepare_all_cmds(cmd, fds, 1);
	if (infos[0].builtin != -1)
		ret = launch_builtin(cmd, infos, fds);
	else
		pids = launch_all(cmd, infos, fds, 1);
	do_all_heredocs(infos, fds->hd_pipes, 1);
	close_fds(fds, 1);
	if (infos[0].builtin == -1)
		waitpid(*pids, &ret, 0);
	free(pids);
	cleanup_all_info(infos, 1);
	return (compute_return_value(ret));
}

static int	launch_builtin(t_cmd *cmd, t_cmd_info *info, t_fds *fds)
{
	int	stdin_clone;
	int	stdout_clone;

	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	dup2(info->i_fd, STDIN_FILENO);
	dup2(info->o_fd, STDOUT_FILENO);
	close_fds(fds, 1);
	info->status = exec_builtin(info->builtin, cmd->args + 1);
	dup2(stdin_clone, STDIN_FILENO);
	dup2(stdout_clone, STDOUT_FILENO);
	close(stdin_clone);
	close(stdout_clone);
	return (info->status);
}
