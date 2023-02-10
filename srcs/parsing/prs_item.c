/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:41:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 12:50:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_token *tok);
static int	get_modifier(t_token *tok);

/*
	Parse the next item.
	An item is either a simple string or a redirection token
	followed by a string.
	Coming accross a redirection token that isn't followed by
	a string results in a syntax error.

	Grammar rule:
	<item> := ['<' | '<<' | '>>' | '>' ] STRING
*/
int	parse_item(t_item **item, t_token **tok)
{
	int		modifier;

	*item = NULL;
	if ((*tok)->type == e_end)
		return (STOP);
	if (is_redirection(*tok))
	{
		modifier = get_modifier(*tok);
		next_token(tok);
		if (assert_token(*tok, e_string) != 0)
			return (SYNTAX_ERROR);
		*item = item_factory(&(t_item){ft_strdup((*tok)->str), modifier, NULL});
		next_token(tok);
	}
	else if ((*tok)->type == e_string)
	{
		*item = item_factory(
				&(t_item){ft_strdup((*tok)->str), NO_MODIFIER, NULL});
		next_token(tok);
	}
	else
		return (STOP);
	return (SUCCESS);
}

static int	is_redirection(t_token *tok)
{
	return (tok->type == e_heredoc
		|| tok->type == e_infile
		|| tok->type == e_append
		|| tok->type == e_outfile);
}

static int	get_modifier(t_token *tok)
{
	if (is_redirection(tok))
		return (tok->type);
	else
		return (NO_MODIFIER);
}
