/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:29:52 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 19:03:23 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(char **args)
{
	int	ret_code;
	int	i;

	i = 0;
	ret_code = 0;
	while (args && *args)
	{
		if (i > 0)
		{
			ft_printf("exit: too many arguments\n");
			return (1);
		}
		ret_code = ft_atoi(*args);
		args++;
		i++;
	}
	// cleanup functions? idk really.
	// TODO: return the correct exit code, from the last run command
	exit(ret_code);
	return (0);
}
