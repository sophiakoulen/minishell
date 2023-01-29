/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:40 by znichola          #+#    #+#             */
/*   Updated: 2023/01/29 12:43:54 by skoulen          ###   ########.fr       */
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

static int	end_of_string(char c, int sq, int dq, int esc)
{
	if (!c)
		return (1);
	if (!sq && !dq && !esc && ft_isspace(c))
		return (1);
	return (0);
}

/*
	Feed the incoming string to the token and advance the input pointer.

	How it works: while another token type is not detected, we increment i.
	If we're then still in a quoted state, we have a syntax error.

	Then, when we've computed the length of the string, we can substr it.

	Finally, we increment the pointer by the length of the string.

	To do: when encountering closing quote, an error status should be returned.
	Important!!
*/
static int	string_detection(t_token *tok, char **str)
{
	int	i;
	int	single_q;
	int	double_q;
	int	esc;

	single_q = 0;
	double_q = 0;
	esc = 0;
	i = 0;
	while (!end_of_string((*str)[i], single_q, double_q, esc) && (int)tok->type == -1)
	{
		if ((*str)[i] == 34 && !single_q && !esc)
			double_q ^= 1U;
		if ((*str)[i] == 39 && !double_q && !esc)
			single_q ^= 1U;
		if (!single_q && !double_q)
			tok->type = check_token_literals(*str + i);
		if ((*str)[i] == '\\' && !esc && !single_q)
			esc = 1;
		else
			esc = 0;
		i++;
	}
	if (single_q || double_q)
	{
		print_error(0, 0, "expecting closing quote");
		return (-1);
	}
	if ((int)tok->type != -1)
		i--;
	tok->type = e_string;
	tok->str = ft_substr(*str, 0, i);
	*str += i;
	return (0);
}

/*
	Returns the next token and advances the input str past it
*/
int	lexer(t_token **tok, char **str)
{
	int	ret;

	ret = 0;
	while (ft_isspace(**str))
		(*str)++;
	*tok = token_factory(NULL, NULL, check_token_literals(*str));
	if ((*tok)->type == e_end)
		;
	else if ((int)(*tok)->type != -1)
		*str = *str + ft_strlen(ret_token_literal((*tok)->type));
	else
		ret = string_detection((*tok), str);
	return (ret);
}
