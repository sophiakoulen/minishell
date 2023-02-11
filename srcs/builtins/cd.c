/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:29:21 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/11 21:56:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(t_env **env);

/*
	cd builtin: Change working directory.

	If no argument is given, we look at the HOME env variable.
	After successful changing of working directory, we update
	the PWD and OLDPWD env variables.
*/
int	exec_cd(char **args, t_env **env, int prev)
{
	char	*home;
	char	*path;

	(void)prev;
	if (!*args)
	{
		home = ret_env_key(*env, "HOME");
		if (!home || !*home)
		{
			print_error("cd", 0, "HOME not set");
			return (1);
		}
		path = home;
	}
	else
		path = *args;
	if (chdir(path) != 0)
	{
		print_error("cd", path, strerror(errno));
		return (1);
	}
	if (update_env(env) != 0)
		return (1);
	return (0);
}

static int	update_env(t_env **env)
{
	char	newpwd[PATH_MAX + 1];
	char	*oldpwd;

	if (getcwd(newpwd, sizeof(newpwd)) != NULL)
	{
		oldpwd = ft_strdup(ret_env_key(*env, "PWD"));
		env_add(env, "PWD", newpwd);
		env_add(env, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	else
	{
		print_error("cd", 0, strerror(errno));
		return (1);
	}
	return (0);
}
