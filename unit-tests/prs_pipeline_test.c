/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:47:47 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 11:15:12 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_tests.h"

int	main(int argc, char **argv)
{
	t_token *tok;
	t_token *start;
	char	*str;

	if (argc == 1)
		return (1);
	str = argv[1];

	ft_printf("\n list of tokens: ", str);
	tok = construct_tok_list(str);
	start = tok;
	print_token_list_minimal(tok);
	printf("\n");

	t_pipeline *p = x_malloc(sizeof(*p), 1);
	parse_pipeline(p, &tok);

	print_pipeline(p);
	pipeline_cleanup(p);
	free(p);

	ft_printf("\n after list  of tokens: ", str);
	print_token_list_minimal(tok);
	printf("\n");

	tok_list_cleanup(start);

	return (0);
}
