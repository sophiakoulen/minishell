/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/07 18:20:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_cleanup(t_tree *tree)
{
	if (!tree)
		return ;
	if (!tree->right && !tree->left)
	{
		pipeline_cleanup(tree->pipeline);
		free(tree);
		return ;
	}
	tree_cleanup(tree->left);
	tree_cleanup(tree->right);
	free(tree);
}

void	pipeline_cleanup(t_list *pipeline)
{
	ft_lstclear(&pipeline, (void (*)(void *))item_list_cleanup);
}
