/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:25:03 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 12:09:14 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_equal(char *str, char **identifier, char **value);
static int	is_valid_identifier(char *str);

/*
	export builtin: set environment variables.

	Perform the environment variable assignments given in arguments.
	Variable assignements are in the form "identifier=value".
	
	If value is empty, like: "identifier=", the value of the identifier
	becomes the empty string.

	If there is an identifier but no succeeding "=" sign, like "identifier",
	nothing is done.

	If identifier is not valid, an error message is printed but export will
	try to set the assignements from the other arguments.

	If no argument is given, export prints the environment variables in
	alphabetical order, in a special order.

	Valid identifiers:
	- contain only digits, letters, underscores
	- cannot start with a digit
*/
int	exec_export(char **args, t_env **env)
{
	int		ret;
	char	*identifier;
	char	*value;

	ret = 0;
	while (*args)
	{
		split_equal(*args, &identifier, &value);
		if (!is_valid_identifier(identifier))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", identifier); //on STDERR!!!!!!
			ret = 1;
		}
		else
		{
			if (value)
			{
				env_add(env, identifier, value);
			}
		}
		args++;
	}
	return (ret);
}

static int	split_equal(char *str, char **identifier, char **value)
{
	int	i;

	*value = NULL;
	i = 0;
	while (str[i] && (i == 0 || str[i] != '='))
	{
		i++;
	}
	*identifier = ft_substr(str, 0, i);
	if (str[i] == '=')
		*value = ft_strdup(str + i + 1);
	return (0);
}

static int	is_valid_identifier(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (*str == '\0');
}
