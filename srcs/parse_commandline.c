/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commandline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:13:42 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 11:11:11 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only for dev and debugging
void	print_token_tree(t_tree *tree);

t_token	*token_factory(t_token *next, char *str, enum e_token_type type)
{
	t_token	*ret;

	ret = (t_token *)allocate(sizeof(t_token), 1);
	ret->next = next;
	ret->str = str;
	ret->type = type;
	return (ret);
}

/**
 * A factory to make new nodes for the tree
 * call with blueprint as NULL or
 * tree_factory(&(t_tree){e_string, tok->str, NULL, NULL})
*/
t_tree	*tree_factory(t_tree *blueprint)
{
	t_tree	*ret;

	ret = (t_tree *)allocate(sizeof(t_tree), 1);
	if (blueprint == NULL)
	{
		ret->type = -1;
		ret->str = NULL;
		ret->left = NULL;
		ret->right = NULL;
	}
	else
	{
		ft_printf("\nthe blue-print at the factory is: ");
		print_token_tree(blueprint);
		ft_printf("\n");
		ret->type = blueprint->type;
		ret->str = blueprint->str;
		ret->left = blueprint->left;
		ret->right = blueprint->right;
		ft_printf("the ret at the factory is: ");
		print_token_tree(ret);
		ft_printf("\n\n");
	}
	return (ret);
}

/**
 * The root of the grammar and the tree comes from this
*/
int	parse_commandline(t_tree **tree, t_token *tok)
{
	ft_printf("got to parse command\n");

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
