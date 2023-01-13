/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:11:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/13 16:07:10 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_info	*prepare_all_cmds(t_pipeline *p, t_fds *fds)
{
	t_cmd_info	*cmd_infos;
	int			i;

	cmd_infos = xmalloc(p->n_cmds * sizeof(*cmd_infos));
	i = 0;
	while (i < p->n_cmds)
	{
		prepare_cmd(p->cmd[i], cmd_infos[i], fds, i, p->n_cmds);
		i++;
	}
	return (cmd_infos);
}

void	prepare_cmd(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n)
{
	info->status = 0;
	info->i_fd = -1;
	info->o_fd = -1;
	info->full_path = 0;
	prepare_cmd_in(cmd, info, fds, i);
	if (!info->status)
		prepare_cmd_out(cmd, info, fds, i, n);
	if (!info->status)
		prepare_cmd_path(cmd, info);
}

static void	prepare_cmd_in(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i)
{
	if (!cmd->in) //get input from pipe or stdin
	{
		if (i == 0)
			info->i_fd = STDIN_FILENO;
		else
			info->i_fd = fds->pipes[i - 1][0];
	}
	else if(cmd->in->type == INFILE) //get input from file
	{
		info->i_fd = open(cmd->in->str, O_RDONLY);
		if (info->i_fd < 0)
		{ 
			perror(cmd->in->str); //later error printing needs to be done in child
			info->status = 1;
		}
	}
	else //get input from heredoc
	{
		info->i_fd = fds->hd_pipes[i][0];
	}
}

static void	prepare_cmd_out(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n)
{
	int	flags;

	if (!cmd->out) //get output to pipe (or stdin)
	{
		if (i == n - 1)
			info->o_fd = STDOUT_FILENO;
		else
			info->o_fd = fds->pipes[i][1];
	}
	else //get output to file
	{
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		if (cmd->out->type == IS_APPEND)
			flags |= O_APPEND;
		info->o_fd = open(cmd->out->str, flags, 0644);
		if (info->o_fd < 0)
		{
			perror(cmd->out->str);
			info->status = 1;
		}
	}
}

static void prepare_cmd_path(t_cmd *cmd, t_cmd_info *info)
{
	
}