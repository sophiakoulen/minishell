/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:40 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 15:09:37 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_exec *exec, int i)
{
	int	stdin_clone;
	int	stdout_clone;

	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	dup2(exec->cmds[i].i_fd, STDIN_FILENO);
	dup2(exec->cmds[i].o_fd, STDOUT_FILENO);
	close_fds(exec);
	exec->cmds[i].status = exec_builtin(exec->cmds[i].builtin,
											exec->cmds[i].args + 1,
											exec->env, exec->prev);
	dup2(stdin_clone, STDIN_FILENO);
	dup2(stdout_clone, STDOUT_FILENO);
	close(stdin_clone);
	close(stdout_clone);
	return (exec->cmds[i].status);
}
