/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:43:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/23 12:10:21 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This will make a new linked list of the found tokens.
 */
int	construct_tok_list(t_token **lst, char *str)
{
	t_token	*end;
	t_token	*tmp;

	*lst = NULL;
	while (1)
	{
		if (lexer(&tmp, &str) != 0)
		{
			token_cleanup(tmp);
			tok_list_cleanup(*lst);
			return (-1);
		}
		if (*lst == NULL)
		{
			*lst = tmp;
			end = *lst;
		}
		else
		{
			end->next = tmp;
			end = end->next;
		}
		if (tmp->type == e_end)
			return (0);
	}
}

void	tok_list_cleanup(t_token *lst)
{
	t_token *previous;

	previous = 0;
	while (lst)
	{
		token_cleanup(previous);
		previous = lst;
		lst = lst->next;
	}
	token_cleanup(previous);
}


void	next_token(t_token **list)
{
	*list = (*list)->next;
}
