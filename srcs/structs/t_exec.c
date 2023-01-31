/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:18:46 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 11:26:53 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**cleanup_pipes(int **pipes, int n);

/*
	Free the contents of exec.
*/
void	cleanup_exec(t_exec *exec)
{
	int	i;

	cleanup_pipes(exec->pipes, exec->n - 1);
	cleanup_pipes(exec->hd_pipes, exec->n);
	strarr_cleanup(exec->path);
	i = 0;
	while (i < exec->n)
	{
		cmd_cleanup(&exec->cmds[i]);
		i++;
	}
	free(exec->cmds);
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
