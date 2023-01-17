/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_commandline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:13:42 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 18:16:40 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The root of the grammar and the tree comes from this
*/
int	parse_commandline(t_tree **tree, t_token *tok)
{
	(void)tree;
	(void)tok;
	/*
	t_tree	*root;

	root = tree_factory(NULL);
	if (tok->type == e_end)
	{
		root->type = e_end;
		*tree = root;
		return (SUCCESS);
	}
	parse_pipeline(&root, &tok);
	*tree = root;
	*/
	return (SUCCESS);
}
