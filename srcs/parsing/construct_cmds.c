/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 21:05:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


int	construct_cmd(t_token **tok, t_cmd *cmd)
{
	t_redir	*tmp;

	cmd = cmd_factory(NULL);
	while (1)
	{
		parse_item(&tmp, tok);

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
