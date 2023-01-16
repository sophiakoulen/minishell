/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:17 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 13:38:31 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
