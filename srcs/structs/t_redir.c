/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:26 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 14:20:08 by znichola         ###   ########.fr       */
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
		ret->type = 0;
		ret->str = NULL;
	}
	else
	{
		ret->type = blueprint->type;
		ret->str = blueprint->str;
	}
	return (ret);
}

void	print_redir(t_redir *r)
{
	if (r)
		ft_printf("%2s %-10s", ret_token_literal(r->type), r->str);
}
