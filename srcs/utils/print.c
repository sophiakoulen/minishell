/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:29:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/16 20:18:31 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipeline(t_list *lst)
{
	int	n;

	n = ft_lstsize(lst);
	ft_printf("%d\n", n);
	while (lst)
	{
		print_cmd(lst->content);
		lst = lst->next;
	}
}

void	print_cmd(t_item *lst)
{
	t_item	*current;

	ft_printf("[");
	current = lst;
	while (current)
	{
		if (current->modifier == NO_MODIFIER)
			ft_printf("%s ", current->word);
		current = current->next;
	}
	ft_printf("][");
	current = lst;
	while (current)
	{
		if (current->modifier != NO_MODIFIER)
			ft_printf("%s %s ",
				ret_token_literal(current->modifier), current->word);
		current = current->next;
	}
	ft_printf("]\n");
}
