/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:18:54 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/13 15:05:17 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Execute a pipeline containing multiple commands.

	File descriptors are already prepared.

	Return value corresponds to the last command.
*/
int	multiple_commands(t_pipeline *p, t_env *environment, t_fds *fds)
{
	int	*pids;
	int	ret;

	//prepare commands (path finding etc)
	pids = launch_all(p, environment, fds);
	do_all_heredocs(p, fds->hd_pipes);
	close_unused_fds(fds);
	ret = wait_all(pids);
	free(pids);
	return (compute_return_value(ret));
}

int	*launch_all(t_pipeline *p, t_env *environment, t_fds *fds)
{
	int	*pids;
	int	i;

	pids = xmalloc(p->n_cmds * sizeof(int));
	i = 0;
	while (i < p->n_cmds)
	{
		pids[i] = launch_child();
		i++;
	}
	return (pids);
}

int	wait_all(int n, int *pids)
{
	int	exit_status;
	int	i;

	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	return (status);
}

int	launch_child(t_cmd *cmd, t_cmd_info *info, t_env *environment)
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
		close_unused_fd();
		
		if (is_builtin(cmd))
		{
			exec_builtin(cmd, environment);
		}
		else
		{
			exec_cmd(cmd, info, environment);
		}
		close(0);
		close(1);
		exit(1);
	}
	return (pid);
}


