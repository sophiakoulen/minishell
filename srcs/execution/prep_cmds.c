/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:11:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 15:46:33 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_redirs(t_item *lst, t_cmd *cmd, t_exec *exec);
static int	update_fd_in(t_cmd *cmd, t_item *redir, t_exec *exec);
static int	update_fd_out(t_cmd *cmd, t_item *redir, t_exec *exec);
static void	prepare_cmd_path(t_cmd *cmd, t_exec *exec);
static void	init_cmd(t_cmd *cmd);
static void	prepare_cmd(t_item *lst, t_exec *exec, int i);
static char	**extract_args(t_item *lst);

t_exec	*prepare_pipeline(t_list *pipeline, t_env **env, int prev)
{
	t_exec	*exec;
	int			i;

	exec = x_malloc(sizeof(*exec), 1);
	init_exec(pipeline, exec, env, prev);
	i = 0;
	while (pipeline)
	{
		prepare_cmd(pipeline->content, exec, i);
		pipeline = pipeline->next;
		i++;
	}
	return (exec);
}

static void	prepare_cmd(t_item *lst, t_exec *exec, int i)
{
	t_cmd	*cmd;

	cmd = &exec->cmds[i];
	init_cmd(cmd);
	cmd->i = i;
	cmd->n = exec->n;
	cmd->args = extract_args(lst);
	prepare_redirs(lst, cmd, exec);
	if (cmd->status == 0)
		prepare_cmd_path(cmd, exec);
}

static char	**extract_args(t_item *lst)
{
	char	**args;
	t_item	*current;
	int		i;

	i = 0;
	current = lst;
	while (current)
	{
		if (current->modifier == NO_MODIFIER)
			i++;
		current = current->next;
	}
	args = x_malloc(sizeof(*args), i + 1);
	current = lst;
	i = 0;
	while (current)
	{
		if (current->modifier == NO_MODIFIER)
		{
			args[i] = current->word;
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->i_fd = -1; //maybe default to 0
	cmd->o_fd = -1;//maybe default to 1
	cmd->full_path = NULL;
	cmd->status = 0;
	cmd->has_heredoc = 0;
	cmd->hd_delim = NULL;
	cmd->hd_buffer = NULL;
	cmd->builtin = -1;
	cmd->args = NULL;
	cmd->i = -1;
	cmd->n = -1;
}


static void	prepare_redirs(t_item *lst, t_cmd *cmd, t_exec *exec)
{
	t_item	*current;

	if (cmd->i == 0)
		cmd->i_fd = STDIN_FILENO;
	else
		cmd->i_fd = exec->pipes[cmd->i - 1][0];
	if (cmd->i == cmd->n - 1)
		cmd->o_fd = STDOUT_FILENO;
	else
		cmd->o_fd = exec->pipes[cmd->i][1];
	current = lst;
	while (current)
	{
		if (update_fd_in(cmd, current, exec) == -1)
			break ;
		if (update_fd_out(cmd, current, exec) == -1)
			break ;
		current = current->next;
	}
}

/*
	Question: Should errors be printed in child?
*/
static int	update_fd_in(t_cmd *cmd, t_item *redir, t_exec *exec)
{
	if (redir->modifier == e_infile)
	{
		cmd->i_fd = open(redir->word, O_RDONLY);
		if (cmd->i_fd < 0)
		{
			print_error(0, redir->word, strerror(errno));
			cmd->status = 1;
			return (-1);
		}
		exec->infile_fds[cmd->i] = cmd->i_fd;
	}
	else if (redir->modifier == e_heredoc)
	{
		cmd->has_heredoc = 1;
		cmd->hd_delim = redir->word;
		cmd->i_fd = exec->hd_pipes[cmd->i][0];
	}
	return (0);
}

/*
*/
static int	update_fd_out(t_cmd *cmd, t_item *redir, t_exec *exec)
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
		print_error(0, redir->word, strerror(errno));
		cmd->status = 1;
		return (-1);
	}
	exec->outfile_fds[cmd->i] = cmd->o_fd;
	return (0);
}

static void	prepare_cmd_path(t_cmd *cmd, t_exec *exec)
{
	if (!cmd->args[0])
		return ;
	if (ret_builtin_enum(cmd->args[0]) != -1)
		cmd->builtin = ret_builtin_enum(cmd->args[0]);
	else
		cmd->status = find_cmd(exec->path, cmd->args[0], &(cmd->full_path));
}
