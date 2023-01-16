/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:39:06 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 15:55:54 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token *tok;
	char	*str;

	if (argc == 1)
		return (1);
	str = argv[1];
	ft_printf("\n list of tokens: ", str);
	tok = construct_tok_list(str);
	print_token_list_minimal(tok);
	printf("\n");

	t_cmd *cmd;
	parse_cmd(&tok, &cmd);

	print_cmd(cmd);

	ft_printf("\n after list  of tokens: ", str);
	print_token_list_minimal(tok);
	printf("\n");

	exit(0);
	return (0);
}
