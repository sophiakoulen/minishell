/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expansion_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:54:24 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 15:19:53 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_words(t_list *words)
// {
// 	if (!words)
// 		return ;
// 	ft_printf("{%s} ", (char *)words->content);
// 	print_words(words->next);
// }

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	char * str = str_expansion(argv[1]);
	ft_printf("{%s}", str);
	ft_printf("\n");
	free(str);
}
