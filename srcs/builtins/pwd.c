/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:13:18 by znichola          #+#    #+#             */
/*   Updated: 2023/01/20 16:42:46 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd buitin: print absolute pathname of working directory

	Should we print errors if options are supplied?
*/
int	exec_pwd(char **args)
{
	char	cwd[PATH_MAX + 1];

	(void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
	return (0);
}
