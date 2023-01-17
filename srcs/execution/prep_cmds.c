/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:11:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 10:42:22 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_cmd_in(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i);
static void	prepare_cmd_out(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n);
static void prepare_cmd_path(t_cmd *cmd, t_cmd_info *info);
static void	prepare_cmd(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n);

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n)
{
	t_cmd_info	*infos;
	int			i;

	infos = x_malloc(n, sizeof(*infos));
	i = 0;
	while (i < n)
	{
		prepare_cmd(&cmds[i], &infos[i], fds, i, n);
		i++;
	}
	return (infos);
}

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

static void	prepare_cmd(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n)
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
	int	fd;

	if (!cmd->in) //get input from pipe or stdin
	{
		if (i == 0)
			fd = STDIN_FILENO;
		else
			fd = fds->pipes[i - 1][0];
	}
	else if(cmd->in->type == e_infile) //get input from file
	{
		fd = open(cmd->in->str, O_RDONLY);
		if (fd < 0)
		{ 
			perror(cmd->in->str); //later error printing needs to be done in child
			info->status = 1;
		}
		fds->infile_fds[i] = fd;
	}
	else //get input from heredoc
	{
		fd = fds->hd_pipes[i][0];
	}
	info->i_fd = fd;
}

static void	prepare_cmd_out(t_cmd *cmd, t_cmd_info *info, t_fds *fds, int i, int n)
{
	int	flags;
	int	fd;

	if (!cmd->out) //get output to pipe (or stdin)
	{
		if (i == n - 1)
			fd = STDOUT_FILENO;
		else
			fd = fds->pipes[i][1];
	}
	else //get output to file
	{
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		if (cmd->out->type == e_append)
			flags |= O_APPEND;
		fd = open(cmd->out->str, flags, 0644);
		if (fd < 0)
		{
			perror(cmd->out->str);
			info->status = 1;
		}
		fds->outfile_fds[i] = fd;
	}
	info->o_fd = fd;
}

static void prepare_cmd_path(t_cmd *cmd, t_cmd_info *info)
{
	//environment variables not handled yet so a default path is used!
	char	*path[] = {"/bin", "/usr/bin", 0};

	if (cmd->args)
	{
		info->status = find_cmd(path, cmd->args[0], &(info->full_path));
	}
	else
	{
		info->status = 1;
	}
}