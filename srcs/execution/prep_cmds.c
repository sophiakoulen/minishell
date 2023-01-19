/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:11:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/19 16:08:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_redirs(t_cmd_info *cmd, t_fds *fds);
static int	update_fd_in(t_cmd_info *cmd, t_item *redir, t_fds *fds);
static int	update_fd_out(t_cmd_info *cmd, t_item *redir, t_fds *fds);
static void	prepare_cmd_path(t_cmd_info *cmd, char **path);

t_cmd_info	*prepare_all_cmds(t_cmd *cmds, t_fds *fds, int n, t_env *env)
{
	t_cmd_info	*infos;
	int			i;
	char		**path;
	char		**env_array;

	env_array = env_to_strarr(env);
	path = extract_path(env_array);
	strarr_cleanup(env_array);
	infos = x_malloc(n, sizeof(*infos));
	i = 0;
	while (i < n)
	{
		init_info(&infos[i], &cmds[i], i, n);
		prepare_redirs(&infos[i], fds);
		if (infos[i].status == 0)
			prepare_cmd_path(&infos[i], path);
		i++;
	}
	strarr_cleanup(path);
	return (infos);
}

static void	prepare_redirs(t_cmd_info *cmd, t_fds *fds)
{
	t_list	*lst;
	t_item	*redir;

	if (cmd->i == 0)
		cmd->i_fd = STDIN_FILENO;
	else
		cmd->i_fd = fds->pipes[cmd->i - 1][0];
	if (cmd->i == cmd->n - 1)
		cmd->o_fd = STDOUT_FILENO;
	else
		cmd->o_fd = fds->pipes[cmd->i][1];
	lst = cmd->redirs;
	while (lst)
	{
		redir = lst->content;
		if (update_fd_in(cmd, redir, fds) == -1)
			break ;
		if (update_fd_out(cmd, redir, fds) == -1)
			break ;
		lst = lst->next;
	}
}

/*
	TO DO: "minishel: " should be prepended to error msg

	Question: Should errors be printed in child?
*/
static int	update_fd_in(t_cmd_info *cmd, t_item *redir, t_fds *fds)
{
	if (redir->modifier == e_infile)
	{
		cmd->i_fd = open(redir->word, O_RDONLY);
		if (cmd->i_fd < 0)
		{
			perror(redir->word);
			cmd->status = 1;
			return (-1);
		}
		fds->infile_fds[cmd->i] = cmd->i_fd;
	}
	else if (redir->modifier == e_heredoc)
	{
		cmd->has_heredoc = 1;
		cmd->heredoc_delim = redir->word;
		cmd->i_fd = fds->hd_pipes[cmd->i][0];
	}
	return (0);
}

/*
	TO DO: "minishel: " should be prepended to error msg
*/
static int	update_fd_out(t_cmd_info *cmd, t_item *redir, t_fds *fds)
{
	int	flags;

	if (redir->modifier != e_outfile && redir->modifier != e_append)
	{
		return (0);
	}
	flags = O_WRONLY | O_TRUNC | O_CREAT;
	if (redir->modifier == e_append)
	{
		flags |= O_APPEND;
	}
	cmd->o_fd = open(redir->word, flags, 0644);
	if (cmd->o_fd < 0)
	{
		perror(redir->word);
		cmd->status = 1;
		return (-1);
	}
	fds->outfile_fds[cmd->i] = cmd->o_fd;
	return (0);
}

static void	prepare_cmd_path(t_cmd_info *cmd, char **path)
{
	if (cmd->args[0])
	{
		if (ret_builtin_enum(cmd->args[0]) != -1)
			cmd->builtin = ret_builtin_enum(cmd->args[0]);
		else
			cmd->status = find_cmd(path, cmd->args[0], &(cmd->full_path));
	}
}
