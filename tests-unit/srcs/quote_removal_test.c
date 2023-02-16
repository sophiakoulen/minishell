/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:54:24 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 12:19:05 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)envp;
	if (argc != 2)
		return (0);
	str = quote_removal(argv[1]);
	ft_printf("{%s}", str);
	ft_printf("\n");
	free(str);
}
