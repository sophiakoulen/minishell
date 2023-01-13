/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:17:15 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 10:22:05 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_token_tree(t_tree *tree)
{
	if (tree->type == e_string)
	{
		ft_printf("{%s}", tree->str);
	}
	else
	{
		if (tree->type == e_end)
			ft_printf("end");
		else
			ft_printf("%s ", ret_token_literal(tree->type));
	}
	if (tree->left)
		print_token_tree(tree->left);
	else if (tree->right)
		print_token_tree(tree->right);
}

int	main(int argc, char **argv)
{
	t_token	*tok;
	t_tree	*tree;
	char	*str;

	if (argc != 2)
		return (1);
	str = argv[1];
	tok = construct_tok_list(str);

	printf("\n\nlist of found tokens \n");
	print_token_list_minimal(tok);
	printf("\n\n\n    ~-~-~-~-~\n\n");

	parse_commandline(&tree, tok);

	printf("\n    ~-~-~-~-~\n");
	ft_printf("\nprinted tree\n");
	print_token_tree(tree);

	printf("\n");
	return (0);
}
