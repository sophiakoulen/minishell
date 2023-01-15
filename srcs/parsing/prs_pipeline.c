/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 08:04:32 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// only for dev and debugging
void	print_token_tree(t_tree *tree);

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
	if ((*tok)->type == e_string && (*tok)->next && (*tok)->next->type == e_pipe)
	{
		t_tree	*right = 0;
		t_tree	*left = 0;
		// ft_printf("adress is: %p\n", &left);
		parse_command(&left, tok);
		*tok = (*tok)->next;
		parse_pipeline(&right, tok);
		*tree = tree_factory(&(t_tree){e_pipe, NULL, left, right});

		return (SUCCESS);
	}
	else if ((*tok)->type == e_string)
	{
		parse_command(tree, tok);
		return (SUCCESS);
	}
	return (SUCCESS);
}
