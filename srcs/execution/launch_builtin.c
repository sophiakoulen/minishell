/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:40 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/23 17:13:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_cmd_info *cmd, t_fds *fds, t_env **env, int prev)
{
	int	stdin_clone;
	int	stdout_clone;

	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	dup2(cmd->i_fd, STDIN_FILENO);
	dup2(cmd->o_fd, STDOUT_FILENO);
	close_fds(fds, 1);
	cmd->status = exec_builtin(cmd->builtin, cmd->args + 1, env, prev);
	dup2(stdin_clone, STDIN_FILENO);
	dup2(stdout_clone, STDOUT_FILENO);
	close(stdin_clone);
	close(stdout_clone);
	return (cmd->status);
}
