/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:52:30 by znichola          #+#    #+#             */
/*   Updated: 2023/01/22 11:22:17 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	str_cap(char *str)
{
	while(*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}

/*
	shout builtin (custom): like echo but all caps.
*/
int	exec_shout(char **args, t_env **env)
{
	char	*line;
	int		no_newline;

	(void)env;
	if (!args || !*args)
		return (0);
	no_newline = 0;
	if (ft_strlen(args[0]) == 2 &&  args[0][0] == '-' && args[0][1] == 'n')
		no_newline = 1;
	while (*args)
	{
		line = *args;
		str_cap(line);
		ft_printf("%s%s%s", T_RED, line, T_RESET);
		if (!no_newline && args[1] == NULL)
			ft_printf("\n");
		else if (args[1])
			ft_printf(" ");
		args++;
	}
	return (0);
}
