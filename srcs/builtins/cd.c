/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:29:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 16:07:07 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cd builtin: Change working directory.
*/
int	exec_cd(char **args, t_env **env)
{
	(void)env;
	if (!*args)
		return (0);
	if (chdir(*args) != 0)
	{
		perror(*args); //better error printing needed!
		return (1);
	}
	return (0);
}