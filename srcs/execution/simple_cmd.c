/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:10:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 16:39:52 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch_builtin(t_cmd *cmds, t_cmd_info *infos, t_fds *fds);

int	simple_command(t_cmd *cmds, t_fds *fds)
{
	int			*pids;
	t_cmd_info	*infos;
	int			ret;

	pids = NULL;
	infos = prepare_all_cmds(cmds, fds, 1);

	if (infos[0].builtin != -1)
		ret = launch_builtin(cmds, infos, fds);
	else
		pids = launch_all(cmds, infos, fds, 1);

	do_all_heredocs(infos, fds->hd_pipes, 1);

	close_fds(fds, 1);

	if (infos[0].builtin == -1)
		waitpid(*pids, &ret, 0);
	free(pids);
	cleanup_all_info(infos, 1);
	return (compute_return_value(ret));
}

static int	launch_builtin(t_cmd *cmds, t_cmd_info *infos, t_fds *fds)
{
	// launch child
	redirect(infos->i_fd, infos->o_fd);
	close_fds(fds, 1);

	// ft_printf("trying to launch builtin %s\n", ret_builtin_literal(infos[0].builtin));
	infos->status = exec_builtin(infos[0].builtin, cmds->args + 1);

	// close(0);
	// close(1);

	return (infos->status);
	// launch child
}
