/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 10:03:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (SUCCESS);
	}
	return (SUCCESS);
}
