/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 15:12:03 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_pipeline(t_pipeline *p)
{
	int	i;

	i = 0;
	while (i < p->n_cmds)
	{
		expand_cmd(&p->cmds[i]);
		i++;
	}
}

/*
	Currently doesn't do any expansion,
	just translate from one form into the other.
*/
void	expand_cmd(t_cmd *cmd)
{
	t_list	*iter;
	int		i;
	int		len;

	len = ft_lstsize(cmd->args_list);
	cmd->args_array = x_malloc(sizeof(*(cmd->args_array)), len + 1);
	i = 0;
	iter = cmd->args_list;
	while (i < len)
	{
		cmd->args_array[i] = ft_strdup(iter->content); //MALLOC PROTECTION
		iter = iter->next;
	}
	cmd->args_array[i] = 0;
}
