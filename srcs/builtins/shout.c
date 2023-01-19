/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:52:30 by znichola          #+#    #+#             */
/*   Updated: 2023/01/20 00:27:30 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	str_cap(char *str)
// {
// 	while(*str)
// 	{
// 		*str = ft_toupper(*str);
// 		str++;
// 	}
// }

int	exec_shout(char **args)
{
	char	*line;
	int		no_newline;

	if (!args || !*args)
		return (0);
	no_newline = 0;
	if (ft_strlen(args[0]) == 2 &&  args[0][0] == '-' && args[0][1] == 'n')
		no_newline = 1;
	while (*args)
	{
		line = *args;
		// str_cap(line);
		ft_printf("%s%s%s", T_RED, line, T_RESET);
		if (!no_newline && args[1] == NULL)
			ft_printf("\n");
		else if (args[1])
			ft_printf(" ");
		args++;
	}
	return (0);
}
