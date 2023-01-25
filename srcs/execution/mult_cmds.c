/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:18:54 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/25 12:43:48 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_all(int n, int *pids);
static int	launch_child(t_cmd_info *cmd, t_fds *fds, int n, t_env *env, int prev);
static void	exec_cmd(t_cmd_info *cmd, t_fds *fds, t_env *env, int prev);

extern int	g_child_pid;

/*
	Execute a pipeline containing multiple commands.

	File descriptors are already prepared.

	Return value corresponds to the last command.
*/
int	multiple_commands(t_cmd *cmds, t_fds *fds, int n, t_env *env, int prev)
{
	int			*pids;
	t_cmd_info	*infos;
	int			ret;

	infos = prepare_all_cmds(cmds, fds, n, env);
	pids = launch_all(infos, fds, n, env, prev);
	do_all_heredocs(infos, fds->hd_pipes, n);
	cleanup_all_info(infos, n);
	close_fds(fds, n);
	ret = wait_all(n, pids);
	free(pids);
	return (compute_return_value(ret));
}

int	*launch_all(t_cmd_info *cmds, t_fds *fds, int n, t_env *env, int prev)
{
	int	*pids;
	int	i;

	pids = x_malloc(sizeof(*pids), n);
	i = 0;
	while (i < n)
	{
		pids[i] = launch_child(&cmds[i], fds, n, env, prev);
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

static int	launch_child(t_cmd_info *cmd, t_fds *fds, int n, t_env *env, int prev)
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
		g_child_pid = pid;
		redirect(cmd->i_fd, cmd->o_fd);
		close_fds(fds, n);
		exec_cmd(cmd, fds, env, prev);
		close(0);
		close(1);
		exit(cmd->status);
	}
	return (pid);
}

static void	exec_cmd(t_cmd_info *cmd, t_fds *fds, t_env *env, int prev)
{
	char	**env_array;

	if (cmd->status != 0)
	{
		return ;
	}
	if (cmd->builtin != -1)
	{
		cmd->status = launch_builtin(cmd, fds, &env, prev);
	}
	else if (cmd->full_path)
	{
		env_array = env_to_strarr(env);
		execve(cmd->full_path, cmd->args, env_array);
		strarr_cleanup(env_array);
		perror("execve failed");
		cmd->status = 1;
	}
}
