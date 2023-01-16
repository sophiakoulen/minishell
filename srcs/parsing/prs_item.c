/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:41:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/16 14:22:30 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	<item> := ['<' | '<<' | '>>' | '>' ] <string>
*/

#define NO_MODIFIER -1

typedef struct s_item
{
	char	*word;
	int		modifier;
}	t_item;

t_item	*item_factory(t_item *blueprint)
{
	t_item	*item;

	item  = x_malloc(sizeof(*item), 1);
	if (blueprint)
	{
		item->modifier = bluewprint->modifier;
		item->word = blueprint->word;
	}
	else
	{
		item->modifier = NO_MODIFIER;
		item->word = 0;
	}
	return (item);
}

static int is_redir_token(t_token *tok)
{
	return (tok->type == e_heredoc || tok->type == e_in || tok->type == e_out_append || tok->type == e_out);
}

static int get_modifier(t_token *tok)
{
	if (tok->type == e_heredoc)
		return (HEREDOC);
	else if (tok->type == e_in)
		return (INFILE);
	else if (tok->type == e_out_append)
		return (APPEND);
	else if (tok->type == e_out)
		return (OUTFILE)
	else
		return (NO_MODIFIER);
}

int	parse_item(t_item **item, t_token **tok)
{
	int	modifier;
	int	word;

	if ((*tok)->type == e_end)
	{
		*item = NULL;
		return (-2);
	}
	if (is_redir_token(*tok))
	{
		modifier = get_modifier(*tok);
		*tok = (*tok)->next;
		if ((*tok)->type != e_string)
		{
			ft_printf("Syntax error near unexpected token %s\n", ret_token_literal((*tok)->type));
			return (-1);
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
		ft_printf("Syntax error near unexpected token %s\n", ret_token_literal((*tok)->type));
		return (-1);
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
	if ((*tok)->type == e_heredoc || (*tok)->type == e_in
		|| (*tok)->type == e_out_append || (*tok)->type == e_out)
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
