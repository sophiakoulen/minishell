/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:25:03 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/20 17:36:38 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Valid identifiers:
	- contain only digits, letters, underscores
	- cannot start with a digit
*/
int	exec_export(char **args, t_env *env)
{
	int	ret;

	(void)env;
	ret = 0;
	while (*args)
	{
		if (!is_valid_identifier(*args))
		{
			ft_printf("minishell: export: %s: not a valid identifier", *args); //on STDERR!!!!!!
			ret = 1; 
		}
		else
		{
			//do export env
		}
		args++;
	}
	return (ret);
}

static int	is_valid_identifier(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (*str == '\0');
}
