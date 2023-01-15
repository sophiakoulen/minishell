/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 21:53:32 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * word_lst_factory(&(t_redir){str, next})
 * call with blueprint or NULL
 * Don't forget to free it after!
*/
t_word_lst	*word_lst_factory(t_word_lst *blueprint)
{
	t_word_lst	*ret;

	ret = (t_word_lst *)x_malloc(sizeof(t_word_lst), 1);
	if (blueprint == NULL)
	{
		ret->str = NULL;
		ret->next = NULL;
	}
	else
	{
		ret->str = blueprint->str;
		ret->next = blueprint->next;
	}
	return (ret);
}

/**
 * redir_factory(&(t_redir){type, str})
 * call with blueprint or NULL
 * Don't forget to free it after!
*/
t_redir	*redir_factory(t_redir *blueprint)
{
	t_redir	*ret;

	ret = (t_redir *)x_malloc(sizeof(t_redir), 1);
	if (blueprint == NULL)
	{
		ret->type = NULL;
		ret->str = NULL;
	}
	else
	{
		ret->type = blueprint->type;
		ret->str = blueprint->str;
	}
	return (ret);
}

/**
 * cmd_factory(&(t_tree){args, in, out})
 * call with blueprint or NULL
 * Don't forget to free it after!
*/
t_cmd	*cmd_factory(t_cmd *blueprint)
{
	t_cmd	*ret;

	ret = (t_cmd *)x_malloc(sizeof(t_cmd), 1);
	if (blueprint == NULL)
	{
		ret->args = NULL;
		ret->in = NULL;
		ret->out = NULL;
	}
	else
	{
		ret->args = blueprint->args;
		ret->in = blueprint->in;
		ret->out = blueprint->out;
	}
	return (ret);
}


int	construct_cmd(t_token **tok, t_cmd **cmd)
{
	t_redir		*item;
	int			pret;
	t_word_lst	*words;

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
		else if (item->type = e_string)
		{
			ft_lstadd_back(&words, word_lst_factory(&(t_word_lst){item->str, }));
			// free(item);
		}
	}
	*tok = (*tok)->next;
}

int	constuct_cmds(t_token **tok,  t_cmd **cmds, int *n_cmds)
{
	if ((*tok)->type != e_string)
		return (-1);

	*tok = (*tok)->next;
	// parse_command(&((*tree)->right), tok);
	return (SUCCESS);
}
