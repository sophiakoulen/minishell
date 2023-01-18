/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:10:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 14:58:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_builtin(t_cmd *cmds, t_cmd_info *infos, t_fds *fds);

int	simple_cmd_exec(t_cmd *cmds, t_fds *fds)
{
	int			*pid;
	t_cmd_info	*infos;
	int			ret;

	pid = NULL;
	infos = prepare_all_cmds(cmds, fds, 1);

	if (ret_builtin_enum(*cmds->args) != -1)
		ret = launch_builtin(cmds, infos, fds);
	else
		pid = launch_all(cmds, infos, fds, 1);

	do_all_heredocs(infos, fds->hd_pipes, 1);

	cleanup_all_info(infos, 1);

	close_fds(fds, 1);

	if (ret_builtin_enum(*cmds->args) != -1)
		waitpid(*pid, &ret, 0);
	free(pid);
	return (compute_return_value(ret));
}

static int	launch_builtin(t_cmd *cmds, t_cmd_info *infos, t_fds *fds)
{
	// launch child
	redirect(infos->i_fd, infos->o_fd);
	close_fds(fds, 1);

	exec_builtin(ret_builtin_enum(*cmds->args), cmds->args + 1);

	close(0);
	close(1);

	exit(infos->status);
	// launch child
}
