/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:29:52 by znichola          #+#    #+#             */
/*   Updated: 2023/01/23 16:34:36 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str);

/*
	exit builtin: exit the shell

	If an argument is supplied:
		If the argument is numeric, it is used as the exit status.
		If it isn't numeric, an error is printed and the exit status is 255.
	If no argument is supplied, the exit code is that of the last command.
*/
int	exec_exit(char **args, t_env **env, int prev)
{
	int	ret_code;
	int	i;

	(void)env;
	i = 0;
	ret_code = prev;
	while (args && *args)
	{
		if (i > 0)
		{
			print_error("exit", 0, "too many arguments");
			return (1);
		}
		if (!is_numeric(*args))
		{
			print_error("exit", *args, "numeric argument required");
			exit(255);
		}
		ret_code = prev;
		args++;
		i++;
	}
	// cleanup functions?
	exit(ret_code);
	return (0);
}

static int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0');
}
