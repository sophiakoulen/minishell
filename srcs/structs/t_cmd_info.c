/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:13 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 16:00:41 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_all_info(t_cmd_info *infos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(infos[i].full_path);
		i++;
	}
	free(infos);
}

void	init_info(t_cmd_info *info, t_cmd *cmd, int i, int n)
{
	info->status = 0;
	info->builtin = -1;
	info->i_fd = -1;
	info->o_fd = -1;
	info->full_path = 0;
	info->has_heredoc = 0;
	info->heredoc_delim = 0;
	info->args = cmd->args;
	info->redirs = cmd->redirs;
	info->i = i;
	info->n = n;
}
