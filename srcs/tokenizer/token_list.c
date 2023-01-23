/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:43:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/23 11:13:07 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This will make a new linked list of the found tokens.
 */
t_token	*construct_tok_list(char *str)
{
	t_token	*start;
	t_token	*end;
	t_token	*tmp;

	start = NULL;
	while (1)
	{
		tmp = lexer(&str);
		if (start == NULL)
		{
			start = tmp;
			end = start;
		}
		else
		{
			end->next = tmp;
			end = end->next;
		}
		if (tmp->type == e_end)
			return (start);
	}
}

void	tok_list_cleanup(t_token *lst)
{
	t_token *previous;

	previous = 0;
	while (lst)
	{
		if (previous)
			free(previous->str);
		free(previous);
		previous = lst;
		lst = lst->next;
	}
	if (previous)
		free(previous->str);
	free(previous);
}


void	next_token(t_token **list)
{
	*list = (*list)->next;
}
