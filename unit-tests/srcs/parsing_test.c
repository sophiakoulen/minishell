/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:47:47 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/26 12:04:16 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "unit_tests.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token				*tok;
	t_token				*start;
	char				*str;
	t_parsed_pipeline	*parsed;

	if (argc < 2)
		str = "";
	else
		str = argv[1];
	construct_tok_list(&tok, str);
	start = tok;
	if (parse_pipeline(&parsed, &tok) == SUCCESS)
	{
		print_parsed_pipeline(parsed);
		parsed_pipeline_cleanup(parsed);
	}
	tok_list_cleanup(start);
	return (0);
}
