/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:29:52 by znichola          #+#    #+#             */
/*   Updated: 2023/01/22 16:56:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str);
static void	print_arg_error(char *str);

/*
	exit builtin: exit the shell

	If an argument is supplied:
		If the argument is numeric, it is used as the exit status.
		If it isn't numeric, an error is printed and the exit status is 255.
	If no argument is supplied, the exit code is that of the last command.
*/
int	exec_exit(char **args, t_env **env)
{
	int	ret_code;
	int	i;

	(void)env;
	i = 0;
	ret_code = 0; //fetch exit code from last command here!!
	while (args && *args)
	{
		if (i > 0)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (1);
		}
		if (!is_numeric(*args))
		{
			print_arg_error(*args);
			exit(255);
		}
		ret_code = ft_atoi(*args);
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

/*
	Print error on stderr:
		minishell: exit: {arg}: numeric argument required
*/
static void	print_arg_error(char *str)
{
	char	*prefix;
	char	*suffix;
	char	*buffer;
	int		len;

	prefix = "minishell: exit: ";
	suffix = ": numeric argument required\n";
	len = ft_strlen(str) + 17 + 28 + 1;
	buffer = x_malloc(1, len);
	ft_strlcpy(buffer, prefix, len);
	ft_strlcat(buffer, str, len);
	ft_strlcat(buffer, suffix, len);
	write(2, buffer, len);
	free(buffer);	
}
