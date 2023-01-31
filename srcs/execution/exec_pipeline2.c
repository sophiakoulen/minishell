/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:18:54 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 15:24:37 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_all(int n, int *pids);
static int	launch_child(t_exec *exec, int i);
static void	exec_cmd(t_exec *exec, int i);

extern int	g_retn;

/*
	Execute a pipeline containing multiple commands.

	File descriptors are already prepared.

	Return value corresponds to the last command.
*/
int	multiple_commands(t_exec *exec)
{
	int			*pids;
	int			ret;

	read_all_heredocs(exec);
	pids = launch_all(exec);
	write_all_heredocs(exec);
	close_fds(exec);
	ret = wait_all(exec->n, pids);
	free(pids);
	return (compute_return_value(ret));
}

int	*launch_all(t_exec *exec)
{
	int	*pids;
	int	i;

	pids = x_malloc(sizeof(*pids), exec->n);
	i = 0;
	while (i < exec->n)
	{
		pids[i] = launch_child(exec, i);
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

static int	launch_child(t_exec *exec, int i)
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
		g_retn = pid;
		redirect(exec->cmds[i].i_fd, exec->cmds[i].o_fd);
		close_fds(exec);
		exec_cmd(exec, i);
		close(0);
		close(1);
		exit(exec->cmds[i].status);
	}
	return (pid);
}

static void	exec_cmd(t_exec *exec, int i)
{
	char	**env_array;

	if (exec->cmds[i].status != 0)
	{
		return ;
	}
	if (exec->cmds[i].builtin != -1)
	{
		exec->cmds[i].status = launch_builtin(exec, i);
	}
	else if (exec->cmds[i].full_path)
	{
		env_array = env_to_strarr(*exec->env);
		execve(exec->cmds[i].full_path, exec->cmds[i].args, env_array);
		strarr_cleanup(env_array);
		perror("execve failed");
		exec->cmds[i].status = 1;
	}
}
