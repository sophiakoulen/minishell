/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:34 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 16:47:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
	used in unit tests, care if changing format!
	eg: '{echo} | {{test} | {cat{-e}}}'
 */
void	print_token_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left)
	{
		ft_printf("{");
		print_token_tree(tree->left);
		ft_printf("}");
	}
	if (tree->type == e_string)
	{
		ft_printf("%s", tree->str);
	}
	else
	{
		if (tree->type == e_end)
			ft_printf("end");
		else
			ft_printf(" %s ", ret_token_literal(tree->type));
	}
	if (tree->right)
	{
		ft_printf("{");
		print_token_tree(tree->right);
		ft_printf("}");
	}
}
