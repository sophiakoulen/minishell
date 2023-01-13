/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:19:25 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 17:55:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this could also be called parse string.
 * it's job is to check if the current token is a string
 * if so add it to the tree and advance the token list
*/
int	parse_command(t_tree **tree, t_token **tok)
{
	if ((*tok)->type != e_string)
		return (-1);
	*tree = tree_factory(&(t_tree){(*tok)->type, (*tok)->str, NULL, NULL});
	*tok = (*tok)->next;
	return (SUCCESS);
}
