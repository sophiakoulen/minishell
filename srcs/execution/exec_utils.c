/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:39:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/16 19:55:07 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Compute the return value of the pipeline based on the exit
	status of the last process.

	There are 3 possibilities:
	1) Child processes exited normally, and then we need to return
	the exit status of that process.
	2) Execution of child process was interrupted by a signal, and then
	we need to return (128 + sig_num), sig_num being the signal code.
	3) Execution of child process was stopped by signal. Return value
	is similar to 2).
*/
int	compute_return_value(int status)
{
	int	exit_code;
	int	sig_num;

	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		return (exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		sig_num = WTERMSIG(status);
		print_pipe_error(sig_num);
		return (128 + sig_num);
	}
	else
	{
		sig_num = WSTOPSIG(status);
		return (128 + sig_num);
	}
}

/*
	Let file descriptors 0 and 1 point to
	the objects pointed to by the given file descriptors.

	input_fd and output_fd still need to be closed.
*/
int	redirect(int input_fd, int output_fd)
{
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	return (0);
}

/*
	Close all unused file descriptors.
	That means all any file descriptor except 0, 1 and 2.

	The exec structure keeps track of the amount of file
	descriptors we've opened. Because when calling open() or
	dup() the allocated file descriptor is the lowest available,
	we can assume it is correct to call close on any file descriptor
	from 3 to fd_count + 3.
*/
void	close_fds(t_exec *exec)
{
	int	i;

	i = 3;
	while (i < exec->fd_count + 3)
	{
		close(i);
		i++;
	}
}
