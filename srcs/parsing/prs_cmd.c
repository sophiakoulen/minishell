/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 16:08:45 by skoulen          ###   ########.fr       */
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
int	parse_cmd(t_token **tok, t_cmd **cmd)
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
		//cleanup command
		*cmd = 0;
		return (ret);
	}
	if (i == 0)
	{
		//syntax error near unexpected token tok.
		//cleanup command
		*cmd = 0;
		return (SYNTAX_ERROR);
	}
	(*cmd)->args = list_to_args(words);
	ft_lstclear(&words, free);
	return (0);
}

/*int	constuct_cmds(t_token **tok,  t_cmd **cmds, int *n_cmds)
{
	if ((*tok)->type != e_string)
		return (-1);

	*tok = (*tok)->next;
	// parse_command(&((*tree)->right), tok);
	return (SUCCESS);
}*/
