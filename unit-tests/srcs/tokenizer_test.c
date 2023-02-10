/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:01:30 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 12:18:28 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token *tok)
{
	if (!tok)
		return ;
	if (tok->type == e_end)
		ft_printf("token is a type   \"end\"\n");
	else if (tok->type == e_string)
		ft_printf("token is a string \"%s\"\n", tok->str);
	else
		ft_printf("token is a type   \"%s\"\n", ret_token_literal(tok->type));
	if (tok->next)
		print_token_list(tok->next);
}

int	main(int argc, char **argv)
{
	t_token	*tok;
	char	*str;

	if (argc != 2)
		return (1);
	str = argv[1];
	construct_tok_list(&tok, str);
	print_token_list_minimal(tok);
	tok_list_cleanup(tok);
	return (0);
}
