/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:18:54 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/13 15:05:39 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_all(int n, int *pids);
static int	launch_child(t_exec *exec, int i);
static void	exec_cmd(t_exec *exec, int i);

extern int	g_retn;

/*
	Execute a pipeline where forking is necessary.
	- launch the child processes
	- write here-documents to the children
	- close all unused file descriptors
	- wait for the child processes to terminate or stop
	- compute return value that corresponds to the last command
*/
int	multiple_commands(t_exec *exec)
{
	int			*pids;
	int			ret;

	pids = launch_all(exec);
	write_all_heredocs(exec);
	close_fds(exec);
	ret = wait_all(exec->n, pids);
	free(pids);
	return (compute_return_value(ret));
}

/*
	Launch all child processes:
	Allocate an array of n pids and launch a child for each command.
*/
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

/*
	Wait for all child processes from the array of pids
	are terminated or stopped.

	The termination status of the last command is returned.

	Note:
	The WUNTRACED flag allows to wait for stopped processes
	too.
*/
static int	wait_all(int n, int *pids)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, WUNTRACED);
		i++;
	}
	return (status);
}

/*
	Launch a child process that will execute a command.

	Try to fork.
	In the child process that is spawned, apply the appropriate
	redirections, close all unused file descriptors, execute the command.
	If something went wrong, close input and output and exit with the
	appropriate error status.
*/
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
		g_retn = pid; //why? isn't g_retn supposed to be for return value of commandlines?
		redirect(exec->cmds[i].i_fd, exec->cmds[i].o_fd);
		close_fds(exec);
		exec_cmd(exec, i);
		close(0);
		close(1);
		exit(exec->cmds[i].status);
	}
	return (pid);
}

/*
	Execute the command:

	If the status indicates the command is broken, do not do
	anything.
	If the command is a builtin, launch the builtin.
	Else, check first if the command is not empty.
	Then extract the environment, call execve.
	If something went wrong during execve, set the status to 1.

	TO DO: change error message.
*/
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
