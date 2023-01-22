/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:47:55 by znichola          #+#    #+#             */
/*   Updated: 2023/01/22 11:22:56 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env builtin: print environment variables to stdout

	There is no defined order that the variables have to be printed in.
*/
int	exec_env(char **args, t_env **env)
{
	char	**strs;

	(void)args;
	strs = env_to_strarr(*env);
	strarr_print(strs);
	strarr_cleanup(strs);
	return (0);
}
