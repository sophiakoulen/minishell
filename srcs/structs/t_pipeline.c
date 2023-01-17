/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:04:23 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 11:24:00 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipeline(t_pipeline *p)
{
	int	i;

	i = 0;
	while (i < p->n_cmds)
	{
		print_cmd(&p->cmds[i]);
		i++;
	}
}

void	pipeline_cleanup(t_pipeline *p)
{
	int	i;

	i = 0;
	while (i < p->n_cmds)
	{
		cmd_cleanup(&p->cmds[i]);
		i++;
	}
	free(p->cmds);
}
