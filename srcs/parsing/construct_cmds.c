/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 14:10:55 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_args(t_list *lst)
{
	char	**ret;
	char	**tmp;

	ret = (char **)x_malloc(sizeof(char *), ft_lstsize(lst) + 1);
	tmp = ret;
	while (lst)
	{
		*tmp = (char *)x_malloc(sizeof(char), ft_strlen((char *)lst->content));
		// *tmp =
		ft_printf("added: %s\n", lst->content);
		ft_printf("     : %s\n", *tmp);
		lst = lst->next;
		tmp++;
	}
	return (ret);
}


int	construct_cmd(t_token **tok, t_cmd **cmd)
{
	t_redir		*item;
	int			pret;
	t_list		*words;

	words = NULL;
	*cmd = cmd_factory(NULL);
	pret = 1;
	while (pret != -1 && pret != -2)
	{
		pret = parse_item(&item, tok);
		if (item->type == e_in)
			(*cmd)->in = item;
		else if (item->type == e_out)
			(*cmd)->out = item;
		else if (item->type == e_string)
		{
			ft_lstadd_back(&words, list_factory(&(t_list){item->str, NULL}));
			// free(item);
		}
	}
	(*cmd)->args = list_to_args(words);
	ft_lstclear(&words, free);
	// *tok = (*tok)->next;
	return (0);
}

int	constuct_cmds(t_token **tok,  t_cmd **cmds, int *n_cmds)
{
	if ((*tok)->type != e_string)
		return (-1);

	*tok = (*tok)->next;
	// parse_command(&((*tree)->right), tok);
	return (SUCCESS);
}
