/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:48 by znichola          #+#    #+#             */
/*   Updated: 2023/02/09 14:39:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_value(char **buf, char *val, int pos, int extra_space);
static void	dollar_expansion(char **str, char **ret, t_env *env, int retn);
static void	expand_special_param(char **str, char **ret, int retn);
static void	expand_variable(char **str, char **ret, t_env *env);

/*
	Perform parameter expansion, taking into account that dollar-signs
	can be escaped.

	To achieve this, we keep track of a state:
	- MSH_ESCAPED means backslash-escaped
	- MSH_SQUOTE means single-quoted state

	If the current character is an unescaped dollar-sign, we will perform
	dollar-expansion on the following chunk and insert that resulting chunk
	into the `res' buffer.

	Else, we update the state and simply insert the current character in
	the `res' buffer.
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
			free(val);
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
	Insert value into the buffer at a given position, leaving a certain amount
	of free space at the end of the buffer.

	This is a helper function for param_expansion, and that is the reason why
	it is oddly specific.

	Buffer is re-allocated to contain the original contents of the string `*buf',
	+ the contents of the string `val' + `extra_space' amount of bytes.
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
	free(*buf);
	*buf = tmp;
}

/*
	Perform $-sign expansion.

	ret is filled with a heap-allocated result of the expansion.

	the str pointer is advanced until the end of the expanded chunk.
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

/*
	Special parameters:
		$? gets the return value of the last command.
		$# gets "0".
		$!, $@, $* get an empty string.
*/
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

/*
	Variable expansion:
	A dollar sign followed by a valid identifier gets the value of
	the corresponding environment variable.
	If no such environment variable is set, the result is the empty string.

	The extraction of the identifier stops when a character is found that
	cannot be part of an identifier.
	Ex: when expanding $USER!, we will not consider `!' as part of the
	identifier.

	When a corresponding value in the environment is found, we first escape
	some of its characters using backslashes in order to not be confused during
	quote removal. This is done by the escape_special_chars() function.
*/
static void	expand_variable(char **str, char **ret, t_env *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		i++;
	if (i == 1)
	{
		*ret = ft_strdup("$");
		*str += i;
		return ;
	}
	key = ft_substr(*str, 1, i - 1);
	value = ret_env_key(env, key);
	free(key);
	*str += i;
	*ret = escape_special_chars(value);
}
