/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:40 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 11:25:14 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * helper function for the lexer,
 * checks if str at it's currrent point is a token from the list,
 * returns the corresponding enum or -1
 * TODO: maybe it's a good idea to return e_string instead of -1
 * as that's what it really means.
*/
static int	check_token_literals(char *str)
{
	int	i;

	i = -1;
	if (ft_isspace(*str))
		return (100);
	if (*str == '\0' || *str == '\n' || (*str == '\r' && *str + 1 == '\n'))
		return (e_end);
	while (++i < NUM_TOKEN_LITERALS)
	{
		if (!ft_strncmp(str,
				ret_token_literal(i),
				ft_strlen(ret_token_literal(i))))
			return (i);
	}
	return (-1);
}

static void	string_decetion(t_token *tok, char **str)
{
	int	i;
	int	backwards;
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	i = 0;
	while ((*str)[i] && (int)tok->type == -1)
	{
		if ((*str)[i] == 34)
			double_q ^= 1U;
		if ((*str)[i] == 39)
			single_q ^= 1U;
		if (!single_q)
			if (!double_q)
				tok->type = check_token_literals(*str + i);
		i++;
	}
	if (single_q || double_q)
		perror("closing quotes error");
	if ((int)tok->type != -1)
		i--;
	backwards = i - 1;
	while (ft_isspace((*str)[backwards]))
		backwards--;
	tok->type = e_string;
	tok->str = ft_substr(*str, 0, backwards + 1);
	*str += i;
}

/**
 * Returns the next token and anvances the input str past it
 * TODO: this needs to be fixed!
 * The ' " are ignored and we still parce the tokens contained within
*/
static t_token	*lexer(char	**str)
{
	t_token	*tok;

	while (ft_isspace(**str))
		(*str)++;
	tok = x_malloc(sizeof(t_token), 1);
	tok->next = NULL;
	tok->type = check_token_literals(*str);
	if (tok->type == e_end)
		;
	else if ((int)tok->type != -1)
		*str = *str + ft_strlen(ret_token_literal(tok->type));
	else
		string_decetion(tok, str);
	return (tok);
}

/**
 * This will make a new linked list of the found tokens.
 */
t_token	*construct_tok_list(char *str)
{
	t_token	*start;
	t_token	*end;
	t_token	*tmp;

	start = NULL;
	while (1)
	{
		tmp = lexer(&str);
		// ft_printf("lexer type %d %s		", tmp->type, ret_token_literal(tmp->type));
		// ft_printf("lexer str\"%s\"\n", tmp->str);
		if (start == NULL)
		{
			start = tmp;
			end = start;
		}
		else
		{
			end->next = tmp;
			end = end->next;
		}
		if (tmp->type == e_end)
			return (start);
	}
}

void	tok_list_cleanup(t_token *lst)
{
	t_token *previous;

	previous = 0;
	while (lst)
	{
		free(previous->str);
		free(previous);
		previous = lst;
		lst = lst->next;
	}
}
