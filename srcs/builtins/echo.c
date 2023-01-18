/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:52:30 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 19:38:14 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(char **args)
{
	char	*line;
	int		no_newline;
	int		i;

	if (!args || !*args)
		return (0);
	no_newline = 0;
	if (args[0][0] == '-' && args[0][1] == 'n')
	{
		i = 2;
		while (args[0][i] == 'n')
			i++;
		if (args[0][i] == '\0')
		{
			no_newline = 1;
			args++;
		}
	}
	while (*args)
	{
		line = *args;
		ft_printf("%s", line);
		if (!no_newline && args[1] == NULL)
			ft_printf("\n");
		else if (args[1])
			ft_printf(" ");
		args++;
	}
	return (0);
}
