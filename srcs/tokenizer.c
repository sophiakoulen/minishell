/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:40 by znichola          #+#    #+#             */
/*   Updated: 2023/01/11 18:02:21 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_token_literal(enum e_token_type n)
{
	static const char	*tok_strings[NUM_TOKEN_LITERALS] = {
		"|",
		"<<",
		"<",
		">",
		">>",
		"(",
		")",
		"&&",
		"||",
	};

	if (n > NUM_TOKEN_LITERALS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

t_token	*lexer(char	**str)
{
	t_token	*tok;
	int		i;

	tok->next = NULL;
	i = -1;
	while (i++ < NUM_TOKEN_LITERALS)
	{
		if (!ft_strncmp(*str, ret_token_literal(i), ft_strlen(ret_token_literal(i))))
		{
			tok->type = i;
			*str = *str + ft_strlen(ret_token_literal(i));
			return (tok);
		}
	}
	i = 0;
	while (*str[i] && ft_strncmp(*str + i, ret_token_literal(i), ft_strlen(ret_token_literal(i))))
		i++;
	tok->type = e_string;
	tok->str = ft_substr(*str, 0, i);
	return (tok);
}
