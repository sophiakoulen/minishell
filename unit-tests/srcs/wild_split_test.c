/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_split_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 08:26:37 by znichola          #+#    #+#             */
/*   Updated: 2023/02/09 11:54:24 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	**res;

	if (ac != 2)
		return (1);
	res = wild_split(av[1], '*');
	// quote_removal_strarr(res);
	strarr_print(res);
	strarr_cleanup(res);
	return (0);
}
