/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:37 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 13:37:42 by znichola         ###   ########.fr       */
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
 * lst_factory(&(t_redir){str, next})
 * call with blueprint or NULL
 * Don't forget to free it after!
 * TODO: maybe this belonds in it's own file
*/
t_list	*list_factory(t_list *blueprint)
{
	t_list	*ret;

	ret = (t_list *)x_malloc(sizeof(t_list), 1);
	if (blueprint == NULL)
	{
		ret->content = NULL;
		ret->next = NULL;
	}
	else
	{
		ret->content = blueprint->content;
		ret->next = blueprint->next;
	}
	return (ret);
}
