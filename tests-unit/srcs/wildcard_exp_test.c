/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 15:25:59 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*ret;
	char	*ret2;

	(void)av;
	ret = NULL;
	if (ac != 2)
		return (1);
	find_wildcard_matches(&ret, av[1]);
	ret2 = quote_removal(ret);
	free(ret);
	ft_printf("%s\n", ret2);
	if (ret2 != NULL)
		free(ret2);
	return (0);
}
	// ret[ft_strlen(ret)-1] = '\0';
