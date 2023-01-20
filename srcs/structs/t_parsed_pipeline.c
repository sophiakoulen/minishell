/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parsed_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:04:13 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/20 11:50:18 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsed_pipeline	*parsed_pipeline_factory(t_parsed_pipeline *blueprint)
{
	t_parsed_pipeline	*p;

	p = x_malloc(sizeof(*p), 1);
	if (blueprint)
	{
		p->n_cmds = blueprint->n_cmds;
		p->cmds = blueprint->cmds;
	}
	else
	{
		p->n_cmds = 0;
		p->cmds = NULL;
	}
	return (p);
}

void	parsed_pipeline_cleanup(t_parsed_pipeline *p)
{
	int	i;

	i = 0;
	while (i < p->n_cmds)
	{
		parsed_cmd_cleanup(p->cmds[i]);
		i++;
	}
	free(p->cmds);
	free(p);
}

void	print_parsed_pipeline(t_parsed_pipeline *p)
{
	int	i;
	if (!p)
	{
		ft_printf("(NULL)\n");
	}
	else
	{
		ft_printf("%d\n", p->n_cmds);
		i = 0;
		while (i < p->n_cmds)
		{
			print_parsed_cmd2(p->cmds[i]);
			i++;
		}
	}
}