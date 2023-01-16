/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 13:39:44 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this need to be inverted, a piple line is either:
 * <pipeline> ::= <command>
 *              | <command> "|" <pipeline>
*/
int	parse_pipeline(t_tree **tree, t_token **tok)
{
	if ((*tok)->type == e_end)
	{
		*tree = NULL;
		return (-1);
	}
	if ((*tok)->type == e_string)
	{
		parse_command(tree, tok);
	}
	// if ((*tok)->type == e_string && (*tok)->next && (*tok)->next->type == e_pipe)
	if ((*tok)->type == e_pipe)
	{
		t_tree	*right = 0;
		//t_tree	*left = 0;
		*tok = (*tok)->next;
		parse_pipeline(&right, tok);
		*tree = tree_factory(&(t_tree){e_pipe, NULL, *tree, right});
	}
	return (SUCCESS);
}
