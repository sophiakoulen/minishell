/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:29:52 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 13:28:39 by skoulen          ###   ########.fr       */
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

	In interactive mode, "exit\n" is printed
*/
int	exec_exit(char **args, t_env **env, int prev)
{
	int	ret_code;
	int	i;

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
			env_add(env, "EXIT", "yes");
			return (255);
		}
		ret_code = ft_atoi(*args);
		args++;
		i++;
	}
	env_add(env, "EXIT", "yes");
	return (ret_code);
}

static int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0');
}
