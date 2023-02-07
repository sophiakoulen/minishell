/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:22:22 by znichola          #+#    #+#             */
/*   Updated: 2023/02/07 16:57:21 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_items(t_item *t)
{
	if (t == NULL)
		return ;
	if (t->next == NULL)
		ft_printf("{%s}", t->word);
	else
		ft_printf("{%s} ", t->word);
	print_items(t->next);
}

int	main(int argc, char **argv)
{
	t_item	*res;
	t_item	*test;

	if (argc != 2)
		return (1);
	test = item_factory(&(t_item){ft_strdup(argv[1]), -1, NULL});
	res = field_split(test);
	print_items(res);
	item_list_cleanup(res);
	item_list_cleanup(test);
	return (0);
}
