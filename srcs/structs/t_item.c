/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_item.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:29:46 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 16:30:56 by skoulen          ###   ########.fr       */
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

/*
	Frees the item, not the string it points to.
*/
void	item_cleanup(t_item *item)
{
	free(item);
}

/*
	Frees the item and the string it points to.
*/
void	item_cleanup_deep(t_item *item)
{
	free(item->word);
	free(item);
}

void	print_item(t_item *item)
{
	if (item)
	{
		ft_printf("%2s %s", ret_token_literal(item->modifier), item->word);
	}
}

void	print_cmd(t_item *item)
{
	printf("cmd:\n");
	while (item)
	{
		printf("%s\n", item->word);
		item = item->next;
	}
}