/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:41:48 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/12 17:16:48 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increment_shlvl(t_env **env);
static void	assign_and_respond(int *lvl, char **value);

/*
	returns allocated linked list of env structs.

	SHLVL is incremented.
*/
t_env	*init_env(char **envp)
{
	t_env	*ret;
	char	*key;
	char	*value;
	int		index;

	ret = NULL;
	while (envp && *envp)
	{
		index = ft_strchr(*envp, '=') - *envp;
		key = ft_substr(*envp, 0, index);
		value = ft_substr(*envp, index + 1, ft_strlen(*envp + index));
		env_add(&ret, key, value);
		free(key);
		free(value);
		envp++;
	}
	increment_shlvl(&ret);
	return (ret);
}

/*
	incraments the shell level
*/
static void	increment_shlvl(t_env **env)
{
	char	*value;
	int		lvl;

	value = ret_env_key(*env, "SHLVL");
	assign_and_respond(&lvl, &value);
	value = ft_itoa(lvl);
	env_add(env, "SHLVL", value);
	free(value);
}

static void	assign_and_respond(int *lvl, char **value)
{
	if (safe_atoi(lvl, value))
	{
		print_error(0, "SHLVL warning",
			"`shell level is too damn high, reseting to 0'");
		*lvl = 0;
	}
	if (*lvl < 0)
	{
		print_error(0, "SHLVL warning",
			"`don't like this negative shell energy, reseting to 0'");
		*lvl = 0;
	}
	else if (safe_add(lvl, 1))
	{
		print_error(0, "SHLVL warning",
			"`tried to catch me in an overflow! well I reset you to 0'");
		*lvl = 0;
	}
}
