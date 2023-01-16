/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_item.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:29:46 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/16 15:41:27 by skoulen          ###   ########.fr       */
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
	}
	else
	{
		item->modifier = NO_MODIFIER;
		item->word = 0;
	}
	return (item);
}

void	item_cleanup(t_item *item)
{
	free(item);
}
