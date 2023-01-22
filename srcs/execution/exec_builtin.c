/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:21:47 by znichola          #+#    #+#             */
/*   Updated: 2023/01/22 13:24:15 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	If the string corresponds to the name of a builtin, return
	the corresponding enum.
	Else, return -1.
*/
int	ret_builtin_enum(char *str)
{
	int		i;

	i = -1;
	while (++i < NUM_BUILTINS)
	{
		if (!ft_strncmp(str,
				ret_builtin_literal(i),
				ft_strlen(ret_builtin_literal(i))))
			return (i);
	}
	return (-1);
}

/*
	Returns the corresponding string for the builtin,
	or NULL if not in list.
*/
const char	*ret_builtin_literal(enum e_builtin n)
{
	static const char	*tok_strings[NUM_BUILTINS] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		"shout"
	};

	if (n > NUM_BUILTINS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

/*
	Just say we don't support this builtin.
*/
static int	builtin_passthrough(char **args, t_env **env)
{
	(void)args;
	(void)env;
	ft_printf("don't support this builtin yet\n");
	return (0);
}

/**
 * executed the builtin using args as it's argument,
 * or NULL if not in list.
*/
int	exec_builtin(enum e_builtin n, char **args, t_env **env)
{
	static int	(*builtin_arr[NUM_BUILTINS])(char **, t_env **) = {
		exec_echo,
		builtin_passthrough, // cd
		exec_pwd,
		exec_export,
		exec_unset,
		exec_env,
		exec_exit,
		exec_shout,
	};
	if (n > NUM_BUILTINS || n < 0)
		return (builtin_passthrough(args, env));
	return ((builtin_arr)[n](args, env));
}
