/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/27 15:47:24 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**get_pipes(int n);
static int	**cleanup_pipes(int **pipes, int n);
static int	*prepare_all_input(int n);
static int	*prepare_all_output(int n);

t_fds	*prepare_fds(int n)
{
	t_fds	*fds;

	fds = x_malloc(sizeof(*fds), 1);
	fds->infile_fds = prepare_all_input(n);
	fds->outfile_fds = prepare_all_output(n);
	fds->pipes = get_pipes(n - 1);
	fds->hd_pipes = get_pipes(n);
	return (fds);
}

void	cleanup_fds(t_fds *fds, int n_cmds)
{
	cleanup_pipes(fds->pipes, n_cmds - 1);
	cleanup_pipes(fds->hd_pipes, n_cmds);
	free(fds->infile_fds);
	free(fds->outfile_fds);
	free(fds);
}

static int	**get_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = x_malloc(sizeof(*pipes), n);
	i = 0;
	while (i < n)
	{
		pipes[i] = x_malloc(sizeof(int), 2);
		if (pipe(pipes[i]) != 0)
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
	return (0);
}

static int	*prepare_all_input(int n)
{
	int	*input_fds;
	int	i;

	input_fds = x_malloc(sizeof(int), n);
	i = 0;
	while (i < n)
	{
		input_fds[i] = -1;
		i++;
	}
	return (input_fds);
}

static int	*prepare_all_output(int n)
{
	int	*output_fds;
	int	i;

	output_fds = x_malloc(sizeof(int), n);
	i = 0;
	while (i < n)
	{
		output_fds[i] = -1;
		i++;
	}
	return (output_fds);
}
