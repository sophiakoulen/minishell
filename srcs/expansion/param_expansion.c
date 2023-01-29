/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:48 by znichola          #+#    #+#             */
/*   Updated: 2023/01/29 18:27:31 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_value(char **buf, char *val, int pos, int extra_space);
static void	dollar_expansion(char **str, char **ret, t_env *env, int retn);
static void	expand_special_param(char **str, char **ret, int retn);
static void	expand_variable(char **str, char **ret, t_env *env);

/*
	Perform parameter expansion.
	We keep track of a state while iterating over the string.
	If the current character is an unescaped dollar-sign, we insert the
	corresponding value into the buffer.
	Else, we update the state and insert the character into the buffer.
*/
char	*param_expansion(char *str, t_env *env, int retn)
{
	int		state;
	char	*val;
	char	*res;
	int		i;

	state = 0;
	res = x_malloc(1, ft_strlen(str) + 1);
	i = 0;
	while (*str)
	{
		if (*str == '$' && !(state & MSH_ESCAPED) && !(state & MSH_SQUOTE))
		{
			dollar_expansion(&str, &val, env, retn);
			insert_value(&res, val, i, ft_strlen(str) + 1);
			i += ft_strlen(val);
		}
		else
		{
			update_state(str, &state);
			res[i++] = *(str++);
		}
	}
	res[i] = 0;
	return (res);
}

/*
	Helper function for param_expansion2: insert value into the buffer at a
	given position.
	Buffer is re-allocated to contain the original contents of the buffer,
	the value and extra_space.
*/
static void	insert_value(char **buf, char *val, int pos, int extra_space)
{
	int		len;
	char	*tmp;

	(*buf)[pos] = 0;
	len = ft_strlen(*buf) + ft_strlen(val) + extra_space;
	tmp = x_malloc(1, len);
	ft_strlcpy(tmp, *buf, len);
	ft_strlcat(tmp, val, len);
	*buf = tmp;
}

/*
	Perform $-sign expansion.
	Return 0 if string doesn't start with $-sign.
	Return 1 if yes and perform $-sign expansion as follows:

	Special parameters:
	$? gets the return value of the last command.
	$# gets "0".
	$!, $@, $* get an empty string.

	Variable expansion:
	A dollar sign followed by a valid identifier gets the value
	of the corresponding environment variable. If no such
	environment variable is set, the result is the empty string.

	Advance the pointer until end of variable name.

	ret is filled with a heap-allocated result of the expansion.
*/
static void	dollar_expansion(char **str, char **ret, t_env *env, int retn)
{
	if ((*str)[1] && ft_strchr("?!@*#", (*str)[1]))
	{
		expand_special_param(str, ret, retn);
	}
	else
	{
		expand_variable(str, ret, env);
	}
}

static void	expand_special_param(char **str, char **ret, int retn)
{
	if ((*str)[1] == '?')
	{
		*ret = ft_itoa(retn);
	}
	if (ft_isdigit((*str)[1]) || ((*str)[1] && ft_strchr("!@*", (*str)[1])))
	{
		*ret = ft_strdup("");
	}
	if ((*str)[1] == '#')
	{
		*ret = ft_strdup("0");
	}
	*str += 2;
}

static void	expand_variable(char **str, char **ret, t_env *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		i++;
	key = ft_substr(*str, 1, i - 1);
	value = ret_env_key(env, key);
	free(key);
	*str += i;
	*ret = escape_special_chars(value);
}
