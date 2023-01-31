/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_item.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:29:46 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 12:03:51 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_item	*item_factory(t_item *blueprint)
{
	t_item	*item;

	item  = x_malloc(sizeof(*item), 1);
	if (blueprint)
	{
		item->modifier = blueprint->modifier;
		item->word = blueprint->word;
		item->next = blueprint->next;
	}
	else
	{
		item->modifier = NO_MODIFIER;
		item->word = NULL;
		item->next = NULL;
	}
	return (item);
}

void	print_item(t_item *item)
{
	if (item)
	{
		ft_printf("%2s %s", ret_token_literal(item->modifier), item->word);
	}
}

void	item_list_cleanup(t_item *lst)
{
	t_item	*previous;

	previous = 0;
	while (lst)
	{
		if (previous)
			free(previous->word);
		free(previous);
		previous = lst;
		lst = lst->next;
	}
	if (previous)
		free(previous->word);
	free(previous);
}
