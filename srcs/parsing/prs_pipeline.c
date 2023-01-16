/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 15:44:48 by skoulen          ###   ########.fr       */
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
	(void)tree;
	(void)tok;
	/*
	t_cmd	*cmd;
	int		ret;

	if ((*tok)->type == e_end)
	{
		*tree = NULL;
		return (STOP);
	}
	ret = parse_cmd(tree, tok);
	if ((*tok)->type == e_string)
	{
	}
	if ((*tok)->type == e_pipe)
	{
		t_tree	*right = 0;
		//t_tree	*left = 0;
		*tok = (*tok)->next;
		parse_pipeline(&right, tok);
		*tree = tree_factory(&(t_tree){e_pipe, NULL, *tree, right});
	}
	*/
	return (SUCCESS);
}
