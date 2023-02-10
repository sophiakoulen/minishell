/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipeline2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:32 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 12:55:48 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**get_pipes(int n);

void	init_exec(t_list *pipeline, t_exec *exec, t_env **env, int prev)
{
	char	**strs;
	int		n_pipes;

	exec->n = ft_lstsize(pipeline);
	if (exec->n != 0)
		n_pipes = exec->n - 1;
	else
		n_pipes = 0;
	exec->pipes = get_pipes(n_pipes);
	exec->hd_pipes = get_pipes(exec->n);
	exec->fd_count = n_pipes * 2 + exec->n * 2;
	exec->env = env;
	exec->prev = prev;
	strs = env_to_strarr(*env);
	exec->path = extract_path(strs);
	strarr_cleanup(strs);
	exec->cmds = x_malloc(sizeof(*(exec->cmds)), exec->n);
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
