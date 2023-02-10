/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:30 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 12:45:03 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	tree_factory(&(t_tree){e_string, tok->str, NULL, NULL})
	call with blueprint or NULL
	Don't forget to free it after!
 */
t_token	*token_factory(t_token *next, char *str, enum e_token_type type)
{
	t_token	*ret;

	ret = (t_token *)x_malloc(sizeof(t_token), 1);
	ret->next = next;
	ret->str = str;
	ret->type = type;
	return (ret);
}

void	token_cleanup(t_token *tok)
{
	if (tok)
		free(tok->str);
	free(tok);
}

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

	if (n == e_end)
		return ("newline");
	if (n > NUM_TOKEN_LITERALS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

/*
	prints {string} and tokens as them selves
	eg: {diff} < ( {echo} {"$2"} ) < ( {echo} {"$RES"} ) end
	used in unit tests, care if changing format!
 */
void	print_token_list_minimal(t_token *tok)
{
	if (!tok)
		return ;
	if (tok->type == e_end)
		ft_printf("end");
	else if (tok->type == e_string)
		ft_printf("{%s} ", tok->str);
	else
		ft_printf("%s ", ret_token_literal(tok->type));
	if (tok->next)
		print_token_list_minimal(tok->next);
}
