/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:29:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/25 17:23:08 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cd builtin: Change working directory.

	TO DO: Update $PWD and $OLDPWD variables.
*/
int	exec_cd(char **args, t_env **env, int prev)
{
	char	newpwd[PATH_MAX + 1];
	char	*oldpwd;

	(void)prev;
	if (!*args)
		return (0);
	if (chdir(*args) != 0)
	{
		print_error("cd", *args, strerror(errno));
		return (1);
	}
	if (getcwd(newpwd, sizeof(newpwd)) != NULL)
	{
		oldpwd = ret_env_key(*env, "PWD");
		if (oldpwd == NULL)
			oldpwd = ft_strdup("");
		env_add(env, "PWD", newpwd);
		env_add(env, "OLDPWD", oldpwd);
	}
	else
	{
		print_error("pwd", 0, strerror(errno));
		return (1);
	}
	return (0);
}
