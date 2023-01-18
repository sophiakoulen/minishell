/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:17:15 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 08:56:22 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "unit_tests.h"

int	main(int argc, char **argv)
{
	t_token	*tok;
	t_tree	*tree;
	char	*str;

	if (argc != 2)
		return (1);
	str = argv[1];
	tok = construct_tok_list(str);

	// printf("\n\nlist of found tokens \n");
	// print_token_list_minimal(tok);
	// printf("\n\n\n    ~-~-~-~-~\n\n");

	parse_commandline(&tree, tok);

	// printf("\n    ~-~-~-~-~\n");
	// ft_printf("\nprinted tree\n");

	// print_token_tree(tree);
	auto_print_tree(tree);

	// printf("\n");
	return (0);
}
