/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 11:26:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only for dev and debugging
void	print_token_tree(t_tree *tree);

int	parse_pipeline(t_tree **tree, t_token **tok)
{
	ft_printf("got to the pipeline!!\n");

	if ((*tok)->type == e_pipe)
	{
		perror("syntax error next to |");
		exit(1);
	}
	if ((*tok)->type == e_string)
	{
		(*tree)->left = tree_factory(&(t_tree){e_string, (*tok)->str, NULL, NULL}); //leaf node it ends here
		(*tree)->right = tree_factory(NULL);
		tok = &(*tok)->next;
		*tree = (*tree)->right;

		ft_printf("sdfsd\n");
		ft_printf("adress of leaf %p\n", *tree);
		// print_token_tree((*tree)->left);
		ft_printf("sdfsd\n");

		return (SUCCESS);
	}
	return (SUCCESS);
}
