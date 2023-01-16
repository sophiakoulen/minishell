/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:39:06 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 10:54:44 by znichola         ###   ########.fr       */
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

void	print_args(char **args)
{
	int	count;

	count = 0;
	while(*args)
	{
		ft_printf("%2d. %s\n", count, *args);
		args++;
		count++;
	}
}

void	print_redir(t_redir *r)
{
	if (r)
		ft_printf("%2s %-10s", ret_token_literal(r->type), r->str);
}

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
	construct_cmd(&tok, &cmd);

	ft_printf("cmd ..................\n in: ");
	print_redir(cmd->in);
	ft_printf("\nout: ");
	print_redir(cmd->out);
	ft_printf("\n");
	print_args(cmd->args);

	ft_printf("\n after list  of tokens: ", str);
	print_token_list_minimal(tok);
	printf("\n");
	exit(0);
	return (0);
}
