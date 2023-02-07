/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:34:18 by znichola          #+#    #+#             */
/*   Updated: 2023/02/07 13:36:50 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lst_swap(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (b);
}

void	lst_bubble_sort(t_list **lst, int (cmp)(const char *, const char *))
{
	int		sorted;
	t_list	*current;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = *lst;
		while (current && current->next)
		{
			if (0 < cmp(current->content, current->next->content))
			{
				sorted = 0;
				lst_swap(current, current->next);
			}
			current = current->next;
		}
	}
}
