/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 10:40:31 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**get_pipes(int n);
static int	**cleanup_pipes(int **pipes, int n);
static int	*prepare_all_input(int n);
static int	*prepare_all_output(int n);

void	init_exec(t_list *pipeline, t_exec *exec, t_env **env, int prev)
{
	char	**strs;

	exec->n = ft_lstsize(pipeline);
	exec->pipes = get_pipes(exec->n - 1);
	exec->hd_pipes = get_pipes(exec->n);
	exec->infile_fds = prepare_all_input(exec->n);
	exec->outfile_fds = prepare_all_output(exec->n);
	exec->env = env;
	exec->prev = prev;
	strs = env_to_strarr(*env);
	exec->path = extract_path(strs);
	strarr_cleanup(strs);
	exec->cmds = x_malloc(sizeof(*(exec->cmds)), exec->n);
}

/*
	To do: cleanup the cmd_list!
*/
void	cleanup_exec(t_exec *exec)
{
	int	i;

	cleanup_pipes(exec->pipes, exec->n - 1);
	cleanup_pipes(exec->hd_pipes, exec->n);
	free(exec->infile_fds);
	free(exec->outfile_fds);
	strarr_cleanup(exec->path);
	i = 0;
	while (i < exec->n)
	{
		cmd_cleanup(&exec->cmds[i]);
		i++;
	}
	free(exec->cmds);
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

static int	*prepare_all_output(int n) //ridiculous!!
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
