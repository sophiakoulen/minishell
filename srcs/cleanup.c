/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 17:42:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_cleanup(t_list *pipeline)
{
	ft_lstclear(&pipeline, (void (*)(void *))cmd_cleanup);
}

void	cmd_cleanup(t_item *lst)
{
	t_item	*previous;

	previous = 0;
	while (lst)
	{
		lst = lst->next;
		if (previous)
			free(previous->word);
		free(previous);
		previous = lst;
	}
	if (previous)
		free(previous->word);
	free(previous);
}
