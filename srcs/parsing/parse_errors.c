/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:45:29 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 10:50:00 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token(t_token *tok)
{
	ft_printf("Syntax error near unexpected token %s\n", ret_token_literal(tok->type));
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