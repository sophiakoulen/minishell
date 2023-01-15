/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:39:01 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/15 15:38:54 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Compute the return value of the pipeline based on the exit
	status of the last process.

	There are 2 possibilities:
	1) Child processes exited normally, and then we need to return
	the exit status of that process.
	2) Execution of child process was interrupted by a signal, and then
	we need to return (128 + sig_num), sig_num being the signal code.
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
	else
	{
		sig_num = WTERMSIG(status);
		return (128 + sig_num);
	}
}

int	redirect(int input_fd, int output_fd)
{
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	return (0);
}

void	close_fds(t_fds *fds, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		close(fds->hd_pipes[i][0]);
		close(fds->hd_pipes[i][1]);
		close(fds->infile_fds[i]);
		close(fds->outfile_fds[i]);
		if (i == n - 1)
			break ;
		close(fds->pipes[i][0]);
		close(fds->pipes[i][1]);
		i++;
	}
}
