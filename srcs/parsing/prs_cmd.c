/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 11:51:17 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_item *item);
static void	add_item(t_parsed_cmd *cmd, t_item *item);

/* 
	Parse a command.
	Construct an intermediate command structure.

	We need to check that there is at least 1 item,
	else syntax error.
*/
int	parse_cmd(t_parsed_cmd **cmd, t_token **tok)
{
	t_item		*item;
	int			i;
	int			ret;

	*cmd = parsed_cmd_factory(NULL);
	i = 0;
	ret = parse_item(&item, tok);
	while (ret == 0)
	{
		add_item(*cmd, item);
		item_cleanup(item);
		ret = parse_item(&item, tok);
		i++;
	}
	if (ret == SYNTAX_ERROR)
	{
		parsed_cmd_cleanup(cmd);
		return (ret);
	}
	if (i == 0)
	{
		parsed_cmd_cleanup(cmd);
		return (unexpected_token(*tok));
	}
	return (0);
}

static int	is_redirection(t_item *item)
{
	return (item->modifier != NO_MODIFIER);
}

static void	add_item(t_parsed_cmd *cmd, t_item *item)
{
	t_item	*cpy;

	if (is_redirection(item))
	{
		cpy = item_factory(item);
		ft_lstadd_back(&cmd->redirs, list_factory(&(t_list){cpy, NULL}));
	}
	else
	{
		ft_lstadd_back(&cmd->args, list_factory(&(t_list){item->word, NULL}));
	}
}
