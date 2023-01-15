/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:41:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/15 11:27:47 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	<item> := ['<' | '<<' | '>>' | '>' ] <string>
*/

int	parse_item(t_tree **tree, t_token **tok)
{
	t_tree	*tmp;

	if ((*tok)->type == e_end)
	{
		*tree = NULL;
		return (-2);
	}
	if ((*tok)->type == e_heredoc || (*tok)->type == e_in || (*tok)->type == e_out_append
		|| (*tok)->type == e_out)
	{
		tmp = tree_factory(&(t_tree){(*tok)->type, NULL, NULL, NULL});
		*tok = (*tok)->next;
		*tree = tmp;
		if ((*tok)->type != e_string)
		{
			ft_printf("Syntax error near unexpected token %s\n", ret_token_literal((*tok)->type));
			return (-1);
		}
		tmp = tree_factory(&(t_tree){e_string, (*tok)->str, NULL, NULL});
		(*tree)->left = tmp; 
	}
	else if ((*tok)->type == e_string)
	{
		tmp = tree_factory(&(t_tree){e_string, (*tok)->str, NULL, NULL});
		*tree = tmp;
	}
	else
	{
		ft_printf("i got here\n");
		return (-2);
	}
	*tok = (*tok)->next;
	return (SUCCESS);
}