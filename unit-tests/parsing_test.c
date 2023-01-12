/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:17:15 by znichola          #+#    #+#             */
/*   Updated: 2023/01/12 21:24:29 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_tree(t_token *tok)
{

}

int	main(int argc, char **argv)
{
	t_token *tok;
	char	*str;

	if (argc != 2)
		return (1);
	str = argv[1];
	tok = construct_tok_list(str);
	print_token_tree(tok);
	// printf("booo\n");
	return (0);
}
