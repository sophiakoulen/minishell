/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:30:29 by znichola          #+#    #+#             */
/*   Updated: 2023/02/15 17:20:42 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_item	*get_last_item(t_item *t);
void	print_item2(t_item *item);
void	recursive_wrapper(t_item *res, t_item *t);

/*
	**res is empyt and needs filling with the start of the new linked list
	items is a linked list of times to wildcard expand
	the itmes list is freed at the end.
 */
void	expand_wildcards(t_item **res, t_item *items)
{
	char		*wrd_tmp;

	*res = NULL;
	if (items == NULL)
		return ;
	find_wildcard_matches(&wrd_tmp, items->word);
	free(items->word);
	wrd_tmp[ft_strlen(wrd_tmp)-1] = '\0';
	items->word = wrd_tmp;
	*res = field_split(items);
	recursive_wrapper(*res, items->next);
	item_list_cleanup(items);
	return ;
}

void	recursive_wrapper(t_item *res, t_item *t)
{
	t_item	*last;
	char	*wrd_tmp;

	if (t == NULL)
		return ;
	find_wildcard_matches(&wrd_tmp, t->word);
	free(t->word);
	wrd_tmp[ft_strlen(wrd_tmp)-1] = '\0';
	t->word = wrd_tmp;
	last = get_last_item(res);
	last->next = field_split(t);
	recursive_wrapper(res, t->next);
}

t_item	*get_last_item(t_item *t)
{
	if (t == NULL)
		return (t);
	if (t->next == NULL)
		return (t);
	return (get_last_item(t->next));
}

void	print_item2(t_item *item)
{
	if (item)
	{
		ft_printf("tok:%2s wrd:%s nxt:%p",
			ret_token_literal(item->modifier), item->word, item->next);
	}
}
