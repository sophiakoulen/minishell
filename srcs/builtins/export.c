/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:25:03 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/22 13:23:15 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_equal(char *str, char **identifier, char **value);
static void	print_export(t_env *env);
static char	*escape_dquotes(char *str);

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
	if (!*args)
		print_export(*env);
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
				env_add(env, identifier, value);
		}
		args++;
	}
	return (ret);
}

/*
	Split a string into an identifier and a value,
	at the first "=" sign.

	Note that if the first character of the string is "=",
	it is not taken into account as the delimiter.

	If there is no "=" sign, value is set to NULL.
	If the first "=" sign is the last character,
	value is set to the empty string. 
*/
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

/*
	Print environment variables, sorted alphabetically.

	Each variable is printed in the format:
		declare -x {id}="{val}"
	where {id} is the identifier and {val} the value.

	Attention: Note that {val} is printed with double-quotes
	and dollar-signs escaped using backslashes.

	Example: a variable that has identifier var and value hello"$ will
	be printed as follows:
		declare -x var="hello\"\$"
*/
static void	print_export(t_env *env)
{
	t_env	*current;
	char	*escaped;

	sort_env(&env);
	current = env;
	while (current)
	{
		escaped = escape_dquotes(current->value);
		ft_printf("declare -x %s=\"%s\"\n", current->key, escaped);
		free(escaped);
		current = current->next;
	}	
}

/*
	Escape double-quotes and dollar-signs.
	A backslash is placed before each of these characters.
*/
static char	*escape_dquotes(char *str)
{
	int		i;
	char	*res;

	res = x_malloc(1, 2 * ft_strlen(str) + 1);
	i = 0;
	while (*str)
	{
		if (*str == '"' || *str == '$')
		{
			res[i] = '\\';
			i++;
		}
		res[i] = *str;
		i++;
		str++;
	}
	res[i] = 0;
	return (res);
}
