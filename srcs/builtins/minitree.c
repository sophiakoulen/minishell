/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:31:06 by znichola          #+#    #+#             */
/*   Updated: 2023/02/12 11:35:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	prints the argument ast as it's parsed by our tokenizer and parcing
	minitree 'a|b|c|d&&j|g<u|k>o||(w<<e|r&&(b|g<o)||q>>f)'
 */
int	minitree(char **args, t_env **env, int prev)
{
	t_token	*tok_list;
	t_token	*start;
	t_tree	*tree;

	(void)env;
	(void)prev;
	if (!*args)
		return (1);
	if (construct_tok_list(&tok_list, *args) != 0)
	{
		tok_list_cleanup(tok_list);
		return (1);
	}
	start = tok_list;
	if (parse_tree(&tree, &tok_list) != SYNTAX_ERROR)
		print_minitree(tree, NULL, 0);
	trunk_garbage_collector(NULL);
	tree_cleanup(tree);
	tok_list_cleanup(start);
	return (0);
}
