/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:40 by znichola          #+#    #+#             */
/*   Updated: 2023/01/11 22:20:38 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Returns the corresponding string for the token type,
 * or NULL if not in list.
*/
const char	*ret_token_literal(enum e_token_type n)
{
	static const char	*tok_strings[NUM_TOKEN_LITERALS] = {
		"||",
		"|",
		"<<",
		"<",
		">>",
		">",
		"(",
		")",
		"&&",
	};

	if (n > NUM_TOKEN_LITERALS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

int	check_token_literals(char *str)
{
	int	i;

	i = -1;
	// printf("literals \"%s\"\n", str);
	if (*str == '\n' || *str == '\0' || (*str == '\r' && *str == '\n'))
		return (e_end);
	while (++i < NUM_TOKEN_LITERALS)
	{
		// ft_printf("i:%d\n", i);
		if (!ft_strncmp(str, ret_token_literal(i), ft_strlen(ret_token_literal(i))))
		{
			// str = str + ft_strlen(ret_token_literal(i));
			return (i);
		}
	}
	// ft_printf("end of literals\n");
	return (-1);
}

/**
 * TODO: this needs to be fixed!
 * The ' " are ignored and we still parce the tokens contained within
*/
static t_token	*lexer(char	**str)
{
	t_token	*tok;
	int		i;
	int		tmp;

	tok = allocate(sizeof(t_token), 1);
	tok->next = NULL;
	i = -1;
	if (**str == '\n' || **str == '\0')
	{
		tok->type = e_end;
		return (tok);
	}

	while (++i < NUM_TOKEN_LITERALS)
	{
		if (!ft_strncmp(*str, ret_token_literal(i), ft_strlen(ret_token_literal(i))))
		{
			tok->type = i;
			*str = *str + ft_strlen(ret_token_literal(i));
			return (tok);
		}
	}
	// (*str)++;
	i = 0;
	tmp = -1;
	while ((*str)[i] && tmp == -1)
	{
		// ft_printf("HERE %d	", i);
		// ft_printf("%s\n", *str + i);
		// ft_printf("conditions %c tmp %d\n", (*str)[i], tmp);
		tmp = check_token_literals(*str + i);
		i++;
	}
	if (tmp !=  -1)
		i--;
	tok->type = e_string;
	tok->str = ft_substr(*str, 0, i);
	*str += i;
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
		ft_printf("\nhere! %s\n", str);
		tmp = lexer(&str);
		ft_printf("lexer str\"%s\"\n", tmp->str);
		ft_printf("lexer type%d\n", tmp->type);
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
