/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:47:55 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 12:43:36 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env builtin, prints directly to screen
	and cleans up after it's self
 */
int	exec_env(char **args)
{
	strarr_print(args);
	return (0);
}


// void	print_env(t_env *env)
// {
// 	if (env == NULL)
// 		return ;
// 	// ft_printf("%29s = %s\n", env->key, env->value);
// 	ft_printf("%s=%s\n", env->key, env->value);

// 	print_env(env->next);
// }
