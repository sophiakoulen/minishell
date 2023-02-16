/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_trunk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:42 by znichola          #+#    #+#             */
/*   Updated: 2023/02/12 11:38:13 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	trunk_factory(&(t_trunk){str, prev})
	call with blueprint or NULL
	Don't forget to free it after!

	trunks store one line of the binary tree printout, they are
	tricky to keep track of, so a garbage collector is used.

	call trunk_garbage_collector(NULL) to clear stored list.
 */
t_trunk	*trunk_factory(t_trunk *blueprint)
{
	t_trunk	*trunk;

	trunk = (t_trunk *)x_malloc(sizeof(t_trunk), 1);
	if (blueprint)
	{
		trunk->str = blueprint->str;
		trunk->prev = blueprint->prev;
	}
	else
	{
		trunk->str = NULL;
		trunk->prev = NULL;
	}
	trunk_garbage_collector(trunk);
	return (trunk);
}

/*
	print branches of the binary tree
 */
void	trunk_print(t_trunk *t)
{
	if (t == NULL)
		return ;
	trunk_print(t->prev);
	ft_printf("%s", t->str);
}

/*
	pass null to cleanup stored trunks
	used to keep track of all trunks for clean up when done,
	this function is not a-sync safe!
*/
void	trunk_garbage_collector(t_trunk *trunk)
{
	static t_list	*all_trunks;

	if (trunk == NULL)
		ft_lstclear(&all_trunks, free);
	ft_lstadd_back(&all_trunks, ft_lstnew(trunk));
}
