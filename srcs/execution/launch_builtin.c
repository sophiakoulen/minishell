/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:40 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/20 17:03:42 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_cmd *cmd, t_cmd_info *info, t_fds *fds, t_env *env)
{
	int	stdin_clone;
	int	stdout_clone;

	(void)env;
	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	dup2(info->i_fd, STDIN_FILENO);
	dup2(info->o_fd, STDOUT_FILENO);
	close_fds(fds, 1);
	info->status = exec_builtin(info->builtin, cmd->args + 1, env);
	dup2(stdin_clone, STDIN_FILENO);
	dup2(stdout_clone, STDOUT_FILENO);
	close(stdin_clone);
	close(stdout_clone);
	return (info->status);
}
