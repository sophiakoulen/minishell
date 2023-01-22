/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:26:42 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 13:22:04 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	unset builtin: unset environment variables.
*/
int	exec_unset(char **args, t_env **env)
{
	int	ret;

	ret = 0;
	while (*args)
	{
		if (!is_valid_identifier(*args))
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n", *args); //on STDERR!!!!!!
			ret = 1;
		}
		else
		{
			env_remove(env, *args);
		}
		args++;
	}
	return (ret);
}
