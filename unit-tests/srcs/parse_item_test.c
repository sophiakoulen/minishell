/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_item_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:53:44 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/18 08:56:50 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "unit_tests.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token	*tok;
	// t_tree	*tree;
	char	*str;

	if (argc != 2)
		return (1);
	str = argv[1];
	tok = construct_tok_list(str);

	// printf("\n\nlist of found tokens \n");
	// print_token_list_minimal(tok);
	// printf("\n\n\n    ~-~-~-~-~\n\n");

	while (tok && tok->type != e_end)
	{
		// if (parse_item(&tree, &tok) != SUCCESS)
			// break ;
		// ft_printf("tok %s\n", ret_token_literal(tok->type));
	}
	// printf("\n    ~-~-~-~-~\n");
	// ft_printf("\nprinted tree\n");

	// print_token_tree(tree);
	// auto_print_tree(tree);

	// printf("\n");
	return (0);
}