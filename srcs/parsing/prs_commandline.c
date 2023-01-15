/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_commandline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:13:42 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 20:24:27 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only for dev and debugging
void	print_token_tree(t_tree *tree);

t_token	*token_factory(t_token *next, char *str, enum e_token_type type)
{
	t_token	*ret;

	ret = (t_token *)x_malloc(sizeof(t_token), 1);
	ret->next = next;
	ret->str = str;
	ret->type = type;
	return (ret);
}

/**
 * tree_factory(&(t_tree){e_string, tok->str, NULL, NULL})
 * call with blueprint or NULL
 * Don't forget to free it after!
*/
t_tree	*tree_factory(t_tree *blueprint)
{
	t_tree	*ret;

	ret = (t_tree *)x_malloc(sizeof(t_tree), 1);
	if (blueprint == NULL)
	{
		ret->type = -1;
		ret->str = NULL;
		ret->left = NULL;
		ret->right = NULL;
	}
	else
	{
		ret->type = blueprint->type;
		ret->str = blueprint->str;
		ret->left = blueprint->left;
		ret->right = blueprint->right;
	}
	return (ret);
}

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
