/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:34 by znichola          #+#    #+#             */
/*   Updated: 2023/02/07 14:59:39 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * tree_factory(&(t_tree){e_string, tok->str, NULL, NULL})
 * call with blueprint or NULL
 * Don't forget to free it after!
*/
t_tree	*tree_factory(int type, t_tree *lhs, t_tree *rhs, t_list *pipeline)
{
	t_tree	*ret;

	ret = x_malloc(sizeof(*ret), 1);
	ret->type = type;
	ret->left = lhs;
	ret->right = rhs;
	ret->pipeline = pipeline;
	return (ret);
}

/*
	used in unit tests, care if changing format!
	eg: '{echo} | {{test} | {cat{-e}}}'
 */
/*
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
*/
