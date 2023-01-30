/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:29:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 17:47:39 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipeline(t_list *lst)
{
	int	n;

	n = ft_lstsize(lst);
	printf("%d\n", n);
	while (lst)
	{
		print_cmd(lst->content);
		lst = lst->next;
	}
}

void	print_cmd(t_item *lst)
{
	t_item	*current;

	printf("[");
	current = lst;
	while (current)
	{
		if (current->modifier == NO_MODIFIER)
			printf("%s ", current->word);
		current = current->next;
	}
	printf("][");
	current = lst;
	while (current)
	{
		if (current->modifier != NO_MODIFIER)
			printf("%s %s ", ret_token_literal(current->modifier), current->word);
		current = current->next;
	}
	printf("]\n");
}
