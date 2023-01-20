/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:47:55 by znichola          #+#    #+#             */
/*   Updated: 2023/01/20 15:50:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env builtin: print environment variables to stdout

	There is no defined order that the variables have to be printed in.
*/
int	exec_env(char **args)
{
	strarr_print(args);
	return (0);
}
