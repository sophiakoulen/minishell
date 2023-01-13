/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/13 14:57:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*prepare_fds(t_pipeline *p)
{
	t_fds	*fds;

	fds = xmalloc(sizeof(*fds));
	fds->input_fds = prepare_all_input(p);
	fds->output_fds = prepare_all_output(p);
	fds->pipes = get_pipes(p->n_cmds - 1);
	fds->hd_pipes = get_pipes(p->n_cmds);
	return (fds);
}

void	cleanup_fds(t_fds *fds, int n_cmds)
{
	cleanup_pipes(fds->pipes, n_cmds - 1);
	cleanup_pipes(fds->pipes, n_cmds);
	free(fds->input_fds);
	free(fds->output_fds);
	free(fds);
}

static int	**get_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = xmalloc(n * sizeof(*pipes));
	i = 0;
	while (i < n)
	{
		pipes[i] = xmalloc(2 * sizeof(int));
		if (open(pipes[i]) != 0)
		{
			perror("failed to open pipe");
			exit(3);
		}
		i++;
	}
	return (pipes);
}

static int	**cleanup_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static int	prepare_all_input(t_pipeline *p)
{
	int	*input_fds;
	int	i;

	input_fds = xmalloc(p->n_cmds * sizeof(int));
	i = 0;
	while (i < p->n_cmds)
	{
		input_fds[i] = get_single_input(p->cmds[i]);
		i++;
	}
	return (input_fds);
}

static int	prepare_all_output(t_pipeline *p)
{
	int	*output_fds;
	int	i;

	output_fds = xmalloc(p->n_cmds * sizeof(int));
	i = 0;
	while (i < p->n_cmds)
	{
		output_fds[i] = get_single_output(p->cmds[i]);
		i++;
	}
	return (output_fds);
}

static	int get_single_input(t_cmd cmd)
{
	int	fd;

	if (!cmd->in)
	{
		return (-1);
	}
	if (cmd->in->type == INFILE)
	{
		fd = open(cmd->in->str, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->in->str);
		}
		return (fd);
	}
	return (-1);
}

static int	get_single_output(t_cmd cmd)
{
	int	fd;
	int	flags;

	if (!cmd->out)
	{
		return (-1);
	}
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (cmd->out->type == IS_APPEND)
	{
		flags |= O_APPEND;
	}
	fd = open(cmd->out->str, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->out->str);
	}
	return (fd);
}
