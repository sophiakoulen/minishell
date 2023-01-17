/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 18:19:32 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	is_input(t_item *item)
{
	return (item->modifier == e_infile || item->modifier == e_heredoc);
}

static int	is_output(t_item *item)
{
	return (item->modifier == e_outfile || item->modifier == e_append);
}
*/

static int	is_redirection(t_item *item)
{
	return (item->modifier != NO_MODIFIER);
}

/*
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
*/

/* 
	Parse a command.
	Construct an intermediate command structure.

	We need to check that there is at least 1 item,
	else syntax error.
*/
int	parse_cmd(t_parsed_cmd **cmd, t_token **tok)
{
	t_item		*item;
	t_item		*copy;

	t_list		*words;
	t_list		*redirs;

	int			i;
	int			ret;

	words = NULL;
	redirs = NULL;
	i = 0;
	ret = parse_item(&item, tok);
	while (ret == 0)
	{
		if (is_redirection(item))
		{
			copy = item_factory(item);
			ft_lstadd_back(&redirs, list_factory(&(t_list){.content=copy, .next=NULL}));	
		}
		else
		{
			ft_lstadd_back(&words, list_factory(&(t_list){.content=item->word, .next=NULL}));
		}
		item_cleanup(item);
		ret = parse_item(&item, tok);
		i++;
	}
	if (ret == SYNTAX_ERROR)
	{
		ft_lstclear(&words, free);
		ft_lstclear(&redirs, (void(*)(void *))item_cleanup);
		*cmd = 0;
		return (ret);
	}
	if (i == 0)
	{
		*cmd = 0;
		return (unexpected_token(*tok));
	}
	*cmd = parsed_cmd_factory(NULL);
	(*cmd)->args = words;
	(*cmd)->redirs = redirs;
	return (0);
}
