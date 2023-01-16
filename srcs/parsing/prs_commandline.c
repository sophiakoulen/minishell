/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_commandline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:13:42 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 13:32:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The root of the grammar and the tree comes from this
*/
int	parse_commandline(t_tree **tree, t_token *tok)
{
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
	return (SUCCESS);
}
