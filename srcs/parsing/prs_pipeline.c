/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 16:55:16 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this need to be inverted, a piple line is either:
 * <pipeline> ::= <command>
 *              | <command> "|" <pipeline>
*/
int	parse_pipeline(t_list *cmd_list, t_token **tok)
{
	//t_list	*cmd_list;
	t_cmd	*cmd;
	int		ret;
	int		i;

	cmd_list = NULL;
	if ((*tok)->type == e_end)
	{
		return (STOP);
	}
	i = 0;
	while (1)
	{
		ret = parse_cmd(&cmd, tok);
		if (ret != 0)
			break ;
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		i++;
	}
	if (i == 0)
	{
		//cleanup pipeline
		//produce syntax error unexpected token.
		return (SYNTAX_ERROR);
	}
	if (ret == SYNTAX_ERROR)
	{
		//cleanup pipeline
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
