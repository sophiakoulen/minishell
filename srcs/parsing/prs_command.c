/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:19:25 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 10:24:49 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this could also be called parse string.
 * it's job is to check if the current token is a string
 * if the next token is also a string call it's self recursivly
 * <command> ::= <string>
 *             | <string> <command>
*/


// pipeline ::=  command
//            |   pipeline "|" command


int	parse_command(t_tree **tree, t_token **tok)
{
	if ((*tok)->type != e_string)
		return (-1);
	*tree = tree_factory(&(t_tree){(*tok)->type, (*tok)->str, NULL, NULL});
	*tok = (*tok)->next;
	parse_command(&((*tree)->right), tok);
	return (SUCCESS);
}
