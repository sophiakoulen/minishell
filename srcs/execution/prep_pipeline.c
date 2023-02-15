/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:11:39 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/15 14:58:26 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_cmd(t_item *lst, t_exec *exec, int i);
static void	prepare_redirs(t_item *lst, t_cmd *cmd, t_exec *exec);
static int	update_fd_in(t_cmd *cmd, t_item *redir, t_exec *exec);
static int	update_fd_out(t_cmd *cmd, t_item *redir, t_exec *exec);

/*
	Process a linked list of commands and produce an exec structure.

	File descriptors will be opened, arguments extracted and commands
	will be searched for in the PATH variable.
*/
t_exec	*prepare_pipeline(t_list *pipeline, t_env **env, int prev)
{
	t_exec	*exec;
	int		i;

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

/*
	Process a list of items which forms a command.

	We'll assign the right pipe ends to the command.
	Then we'll go through the list of items and update input and output
	file descriptors if redirections are found.

	Each command has a status which is used to determine if the command
	is "broken": should we continue preparing and executing this command?

	If we have found a problem with redirections, we won't search in the PATH.
*/
static void	prepare_cmd(t_item *lst, t_exec *exec, int i)
{
	t_cmd	*cmd;

	cmd = &exec->cmds[i];
	cmd->status = 0;
	cmd->full_path = NULL;
	cmd->hd_buffer = NULL;
	cmd->builtin = -1;
	cmd->args = NULL;
	cmd->i = i;
	cmd->n = exec->n;
	cmd->args = extract_args(lst);
	prepare_redirs(lst, cmd, exec);
	if (cmd->status == 0)
		prepare_cmd_path(cmd, exec);
}

/*
	Prepare input and output file descriptors:

	1. Set default descriptors to be stdin, stdout or the appropriate pipe ends.

	2. Go through the list of items and update input and output file
	descriptors.
*/
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
	Update input file descriptor:

	If item corresponds to a '<' redirection, try to open
	the associated filename. Update the command's status in case
	of failure.

	If item corresponds to a '<<' heredoc, read the heredoc from stdin,
	and set the input fd to the pipe on which it will be transmitted to
	the child.

	The file descriptor count is updated.

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
		exec->fd_count++;
	}
	else if (redir->modifier == e_heredoc)
	{
		read_single_heredoc(&cmd->hd_buffer, redir->word);
		cmd->i_fd = exec->hd_pipes[cmd->i][0];
	}
	return (0);
}

/*
	Update output file descriptor:

	If item corresponds to '>' or '>>', try to open
	the associated filename with the appropriate flags.

	In case of faiure to open, print an error message and
	update the command's status.

	The file descriptor count will be updated.
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
		flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	cmd->o_fd = open(redir->word, flags, 0644);
	if (cmd->o_fd < 0)
	{
		print_error(0, redir->word, strerror(errno));
		cmd->status = 1;
		return (-1);
	}
	exec->fd_count++;
	return (0);
}
