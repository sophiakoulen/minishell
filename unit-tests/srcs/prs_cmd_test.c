/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:39:06 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 16:31:56 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args_list(t_list *args);
static void	print_redirs(t_list *redirs);

int	main(int argc, char **argv)
{
	t_parsed_cmd	*cmd;
	t_token 		*tok;
	char			*str;

	if (argc == 1)
		return (1);
	str = argv[1];
	tok = construct_tok_list(str);
	parse_cmd(&cmd, &tok);
	print_parsed_cmd(cmd);
	return (0);
}

static void	print_args_list(t_list *args)
{
	int	count;

	count = 0;
	while (args)
	{
		ft_printf("%2d. %s\n", count, args->content);
		args = args->next;
		count++;
	}
}

static void	print_redirs(t_list *redirs)
{
	while (redirs)
	{
		print_item(redirs->content);
		redirs = redirs->next;
	}
}
