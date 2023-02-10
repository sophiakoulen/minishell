/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 12:51:14 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Parse a command.
	Construct an intermediate command structure.

	We need to check that there is at least 1 item,
	else syntax error.
*/
int	parse_cmd(t_item **cmd, t_token **tok)
{
	t_item	**current;
	int		i;
	int		ret;

	*cmd = NULL;
	current = cmd;
	i = 0;
	ret = parse_item(current, tok);
	while (ret == 0)
	{
		current = &(*current)->next;
		ret = parse_item(current, tok);
		i++;
	}
	if (ret == SYNTAX_ERROR)
	{
		return (ret);
	}
	if (i == 0)
	{
		return (unexpected_token(*tok));
	}
	return (0);
}
