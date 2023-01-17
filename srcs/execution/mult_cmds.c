/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:18:54 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 15:10:49 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*launch_all(t_cmd *cmds, t_cmd_info *infos, t_fds *fds, int n);
static int	wait_all(int n, int *pids);
static int	launch_child(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int n);
static int	exec_cmd(t_cmd *cmd, t_cmd_info *info);

/*
	Execute a pipeline containing multiple commands.

	File descriptors are already prepared.

	Return value corresponds to the last command.
*/
int	multiple_commands(t_cmd *cmds, t_fds *fds, int n)
{
	int			*pids;
	t_cmd_info	*infos;
	int			ret;

	infos = prepare_all_cmds(cmds, fds, n);
	pids = launch_all(cmds, infos, fds, n);
	cleanup_all_info(infos, n);

	do_all_heredocs(cmds, fds->hd_pipes, n);
	
	close_fds(fds, n);
	
	ret = wait_all(n, pids);
	free(pids);
	return (compute_return_value(ret));
}

static int	*launch_all(t_cmd *cmds, t_cmd_info *infos, t_fds *fds, int n)
{
	int	*pids;
	int	i;

	pids = x_malloc(sizeof(*pids), n);
	i = 0;
	while (i < n)
	{
		pids[i] = launch_child(&cmds[i], &infos[i], fds, n);
		i++;
	}
	return (pids);
}

static int	wait_all(int n, int *pids)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	return (status);
}

static int	launch_child(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int n)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("forking failed");
		exit(4);
	}
	if (pid == 0)
	{
		redirect(info->i_fd, info->o_fd);
		close_fds(fds, n);
		
		exec_cmd(cmd, info);

		close(0);
		close(1);

		exit(info->status);
	}
	return (pid);
}

static int	exec_cmd(t_cmd *cmd, t_cmd_info *info)
{
	if (info->status == 0 && info->full_path)
	{
		execve(info->full_path, cmd->args_array, 0);
		perror("execution of command failed");
		info->status = 1;
	}
	return (0);
}