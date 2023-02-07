/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:16:47 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/07 17:49:25 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_commandline(t_tree **ast, t_token **tok);
static int	parse_conditionnal(t_tree **ast, t_token **tok);

int	parse_tree(t_tree **tree, t_token **tok)
{
	if (parse_commandline(tree, tok) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if ((*tok)->type != e_end)
	{
		unexpected_token(*tok);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

static int	parse_commandline(t_tree **ast, t_token **tok)
{
	t_tree	*rhs;
	int		op;

	*ast = NULL;
	if (parse_conditionnal(ast, tok) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	while (1)
	{
		if ((*tok)->type == e_end || (*tok)->type == e_close_brace)
			break ;
		if ((*tok)->type != e_and && (*tok)->type != e_or)
		{
			unexpected_token(*tok);
			return (SYNTAX_ERROR);
		}
		op = (*tok)->type;
		next_token(tok);
		if ((*tok)->type == e_end)
		{
			unexpected_token(*tok);
			return (SYNTAX_ERROR);
		}
		if (parse_conditionnal(&rhs, tok) != SUCCESS)
			return (SYNTAX_ERROR);
		*ast = tree_factory(op, *ast, rhs, NULL);
	}
	return (SUCCESS);
}

static int	parse_conditionnal(t_tree **ast, t_token **tok)
{
	t_list	*pipeline;

	*ast = NULL;
	if ((*tok)->type == e_open_brace)
	{
		next_token(tok);
		if ((*tok)->type == e_end)
		{
			unexpected_token(*tok);
			return (SYNTAX_ERROR);
		}
		if (parse_commandline(ast, tok) != SUCCESS)
			return (SYNTAX_ERROR);
		if (assert_token(*tok, e_close_brace) != SUCCESS)
			return (SYNTAX_ERROR);
		next_token(tok);
	}
	else
	{
		if (parse_pipeline(&pipeline, tok) != SUCCESS)
			return (SYNTAX_ERROR);
		*ast = tree_factory(e_pipe, NULL, NULL, pipeline);
	}
	return (SUCCESS);
}
