/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 11:38:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd *list_to_array(t_list *lst)
{
	t_cmd	*array;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	array = x_malloc(sizeof(*array), size);
	i = 0;
	while (lst)
	{
		array[i] = *(t_cmd *)lst->content;
		lst = lst->next;
		i++;
	}
	return (array);
}

/**
 * this need to be inverted, a piple line is either:
 * <pipeline> ::= <command>
 *              | <command> "|" <pipeline>
*/
int	parse_pipeline(t_pipeline *pipeline, t_token **tok)
{
	t_list	*lst;
	t_cmd	*cmd;
	int		ret;
	int		i;

	cmd = 0;
	lst = NULL;
	if ((*tok)->type == e_end)
	{
		pipeline->n_cmds = 0;
		pipeline->cmds = 0;
		return (STOP);
	}
	ret = parse_cmd(&cmd, tok);
	i = 0;
	while (ret == 0)
	{
		i++;
		ft_lstadd_back(&lst, ft_lstnew(cmd));

		if ((*tok)->type == e_end)
		{
			break ;
		}

		if (assert_token(*tok, e_pipe) != SUCCESS)
		{
			ret = SYNTAX_ERROR;
			break ;
		}

		*tok = (*tok)->next;
		cmd = 0;
		ret = parse_cmd(&cmd, tok);
	}
	if (i == 0)
	{
		ft_lstclear(&lst, do_nothing);
		return (unexpected_token(*tok));
	}
	if (ret == SYNTAX_ERROR)
	{
		ft_lstclear(&lst, do_nothing);
		return (SYNTAX_ERROR);
	}
	pipeline->n_cmds = i;
	pipeline->cmds = list_to_array(lst);
	ft_lstclear(&lst, do_nothing);
	return (SUCCESS);
}
