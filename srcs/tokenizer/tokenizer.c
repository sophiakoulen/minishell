/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:40 by znichola          #+#    #+#             */
/*   Updated: 2023/02/14 10:55:23 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Checks if str at it's currrent point is a token from the list.
	Return the corresponding enum or e_string.
*/
static int	check_token_literals(char *str)
{
	int			i;
	const char	*tok_literal;

	if (*str == '\0' || *str == '\n' || *str == '#')
		return (e_end);
	i = 0;
	while (i < NUM_TOKEN_LITERALS)
	{
		tok_literal = ret_token_literal(i);
		if (!ft_strncmp(str, tok_literal, ft_strlen(tok_literal)))
			return (i);
		i++;
	}
	return (e_string);
}

/*
	Extract a word from the input string. Quoting is respected.
	The string pointer is advanced past it.

	How it works:
	- while another token type is not detected, we increment i.
	- If we're then still in a quoted state, we have a syntax error.
	- when we've computed the length of the string, we can substr it.
	- advance the str pointer
*/
static int	get_str_token(char **word, char **str)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while ((*str)[i] && (!ft_isspace((*str)[i]) || state))
	{
		update_state(*str + i, &state);
		if (!state && check_token_literals(*str + i) != e_string)
			break ;
		i++;
	}
	*word = ft_substr(*str, 0, i);
	*str += i;
	if (state & MSH_SQUOTE || state & MSH_DQUOTE)
	{
		print_error(0, "syntax error",
			"unexpected end of line when looking for matching quote");
		return (-1);
	}
	return (0);
}

/*
	Returns the next token and advances the input str past it
*/
int	lexer(t_token **tok, char **str)
{
	int		ret;
	char	*word;
	int		tok_type;

	ret = 0;
	while (ft_isspace(**str))
		(*str)++;
	tok_type = check_token_literals(*str);
	if (tok_type != e_string)
	{
		*tok = token_factory(NULL, NULL, tok_type);
		if (tok_type != e_end)
			*str += ft_strlen(ret_token_literal(tok_type));
	}
	else
	{
		ret = get_str_token(&word, str);
		*tok = token_factory(NULL, word, e_string);
	}
	return (ret);
}
