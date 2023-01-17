/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 11:37:57 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_args(t_list *lst)
{
	char	**ret;
	int		size;
	int		i;

	size = ft_lstsize(lst) + 1;
	ret = x_malloc(sizeof(*ret), size);
	i = 0;
	while (i < size - 1)
	{
		ret[i] = ft_strdup((char *)lst->content); //careful, args list is malloced!
		lst = lst->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

/* 
	Parse a command.
	Construct an intermediate command structure.

	We need to check that there is at least 1 item,
	else syntax error.
*/
int	parse_cmd(t_cmd **cmd, t_token **tok)
{
	t_item		*item;
	t_list		*words;
	int			i;
	int			ret;

	words = NULL;
	*cmd = cmd_factory(NULL);
	i = 0;
	ret = parse_item(&item, tok);
	while (ret == 0)
	{
		if (item->modifier == e_infile || item->modifier == e_heredoc)
		{
			(*cmd)->in = redir_factory(&(t_redir){.type=item->modifier, .str=item->word});
		}
		else if (item->modifier == e_outfile || item->modifier == e_append)
		{
			(*cmd)->out = redir_factory(&(t_redir){.type=item->modifier, .str=item->word});
		}
		else
		{
			ft_lstadd_back(&words, list_factory(&(t_list){item->word, NULL}));
		}
		item_cleanup(item);
		ret = parse_item(&item, tok);
		i++;
	}
	if (ret == SYNTAX_ERROR)
	{
		ft_lstclear(&words, free);
		*cmd = 0;
		return (ret);
	}
	if (i == 0)
	{
		*cmd = 0;
		return (unexpected_token(*tok));
	}
	(*cmd)->args = list_to_args(words);
	ft_lstclear(&words, do_nothing);
	return (0);
}
