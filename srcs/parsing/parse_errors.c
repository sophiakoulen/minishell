/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:45:29 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/18 15:29:17 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token(t_token *tok)
{
	const char	*tok_str;
	char		*prefix;
	char		*suffix;
	char		*buffer;
	int			len;

	tok_str = ret_token_literal(tok->type);
	prefix = "minishell: syntax error near unexpected token `";
	suffix = "'\n";
	len = ft_strlen(tok_str) + ft_strlen(prefix) + ft_strlen(suffix) + 1;
	buffer = x_malloc(sizeof(*buffer), len);
	ft_strlcpy(buffer, prefix, len);
	ft_strlcat(buffer, tok_str, len);
	ft_strlcat(buffer, suffix, len);
	write(2, buffer, len);
	free(buffer);
	return (SYNTAX_ERROR);
}

int	assert_token(t_token *tok, enum e_token_type expected)
{
	if (tok->type != expected)
	{
		return (unexpected_token(tok));
	}
	return (SUCCESS);
}
