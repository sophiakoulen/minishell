/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:52:30 by znichola          #+#    #+#             */
/*   Updated: 2023/02/17 09:09:01 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_NEWLINE 1

static int	parse_options(char ***args);
static int	is_valid_option(char *arg);

static void	str_cap(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}

/*
	shout builtin (custom): like echo but all caps.
*/
int	exec_shout(char **args, t_env **env, int prev)
{
	char	*line;
	int		options;

	(void)env;
	(void)prev;
	if (!args)
		return (2);
	options = parse_options(&args);
	while (*args)
	{
		line = *args;
		str_cap(line);
		ft_printf("%s%s%s", T_RED, line, T_RESET);
		if (*(args + 1))
			ft_printf(" ");
		args++;
	}
	if (!(options & NO_NEWLINE))
		ft_printf("\n");
	return (0);
}

/*
	Advance the array pointer while valid options are found.
	Return value is an integer representing the found options,
	bitwise-OR-ed together.

	Currently, the only supported option is "-n", and means
	"no newline".
*/
static int	parse_options(char ***args)
{
	int	options;

	options = 0;
	while (*args && is_valid_option(**args))
	{
		options |= NO_NEWLINE;
		(*args)++;
	}
	return (options);
}

/*
	Checks if a string is a valid option.

	Currently, only "-n" is a valid option.
*/
static int	is_valid_option(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		i = 2;
		while (arg[i] == 'n')
			i++;
		return (arg[i] == '\0');
	}
	return (0);
}
