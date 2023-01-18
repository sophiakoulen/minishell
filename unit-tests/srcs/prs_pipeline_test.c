/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:47:47 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/18 16:27:45 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "unit_tests.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token *tok;
	t_token *start;
	char	*str;

	if (argc < 2)
	{
		str = "";
	}
	else
	{
		str = argv[1];
	}
	tok = construct_tok_list(str);
	start = tok;

	t_parsed_pipeline *p = x_malloc(sizeof(*p), 1);
	parse_pipeline(p, &tok);

	print_parsed_pipeline(p);

	parsed_pipeline_cleanup(p);

	tok_list_cleanup(start);

	return (0);
}
