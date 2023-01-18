/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:41:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/18 10:41:38 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	<item> := ['<' | '<<' | '>>' | '>' ] <string>
*/

static int is_redir_token(t_token *tok)
{
	return (tok->type == e_heredoc || tok->type == e_infile || tok->type == e_append || tok->type == e_outfile);
}

static int get_modifier(t_token *tok)
{
	if (is_redir_token(tok))
		return (tok->type);
	else
		return (NO_MODIFIER);
}

int	parse_item(t_item **item, t_token **tok)
{
	int		modifier;
	char	*word;

	*item = NULL;
	if ((*tok)->type == e_end)
	{
		return (STOP);
	}
	if (is_redir_token(*tok))
	{
		modifier = get_modifier(*tok);
		*tok = (*tok)->next;
		if (assert_token(*tok, e_string) != 0)
		{
			return (SYNTAX_ERROR);
		}
		word = (*tok)->str;
		*item = item_factory(&(t_item){.word=word, .modifier=modifier});
		*tok = (*tok)->next;
	}
	else if ((*tok)->type == e_string)
	{
		word = (*tok)->str;
		modifier = NO_MODIFIER;
		*item = item_factory(&(t_item){.word=word, .modifier=modifier});
		*tok = (*tok)->next;
	}
	else
	{
		return (STOP);
	}
	return (SUCCESS);
}

/*
int	parse_item(t_tree **tree, t_token **tok)
{
	t_tree	*tmp;

	if ((*tok)->type == e_end)
	{
		*tree = NULL;
		return (-2);
	}
	if ((*tok)->type == e_heredoc || (*tok)->type == e_infile
		|| (*tok)->type == e_append || (*tok)->type == e_out)
	{
		tmp = tree_factory(&(t_tree){(*tok)->type, NULL, NULL, NULL});
		*tok = (*tok)->next;
		*tree = tmp;
		if ((*tok)->type != e_string)
		{
			ft_printf("Syntax error near unexpected token %s\n", ret_token_literal((*tok)->type));
			return (-1);
		}
		tmp = tree_factory(&(t_tree){e_string, (*tok)->str, NULL, NULL});
		(*tree)->left = tmp;
	}
	else if ((*tok)->type == e_string)
	{
		tmp = tree_factory(&(t_tree){e_string, (*tok)->str, NULL, NULL});
		*tree = tmp;
	}
	else
	{
		ft_printf("i got here\n");
		return (-2);
	}
	*tok = (*tok)->next;
	return (SUCCESS);
}
*/
