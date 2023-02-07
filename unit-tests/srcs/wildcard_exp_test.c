/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_exp_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:02:38 by znichola          #+#    #+#             */
/*   Updated: 2023/02/06 19:58:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*ret;

	(void)av;
	ret = NULL;
	if (ac != 2)
		return (1);
	wildcard_exp(&ret, av[1]);
	ft_printf("%s\n", ret);
	if (ret != NULL)
		free(ret);
	return (0);
}
	// ret[ft_strlen(ret)-1] = '\0';
