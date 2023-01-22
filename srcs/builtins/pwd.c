/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:13:18 by znichola          #+#    #+#             */
/*   Updated: 2023/01/22 11:22:10 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd buitin: print absolute pathname of working directory

	Should we print errors if options are supplied?
*/
int	exec_pwd(char **args, t_env **env)
{
	char	cwd[PATH_MAX + 1];

	(void)args;
	(void)env;
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
