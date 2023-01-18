/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:21:47 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 16:28:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

/**
 * Returns the corresponding string for the builtin,
 * or NULL if not in list.
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
	};

	if (n > NUM_BUILTINS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

static int	builtin_passthrough(char **args)
{
	// (void)args;
	ft_printf("don't support %s builtin yet\n", *args);
	return (0);
}

/**
 * executed the builtin using args as it's argument,
 * or NULL if not in list.
*/
int	exec_builtin(enum e_builtin n, char **args)
{
	static int	(*builtin_arr[NUM_BUILTINS])(char **) = {
		exec_echo,
		builtin_passthrough, // cd
		exec_pwd,
		builtin_passthrough, // export
		builtin_passthrough, // unset
		exec_env,
		exec_exit,
	};
	if (n > NUM_BUILTINS || n < 0)
		return (builtin_passthrough(args));
	return ((builtin_arr)[n]((char **)args));
}
