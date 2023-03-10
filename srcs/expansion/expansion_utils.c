/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:59:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 16:48:09 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	needs_escaping(char c, int state);

/*
	Check if the character has special meaning and update the state
	accordingly.

	Return value:
	1 if character has special meaning, i.e, it doesn't represent itself.
	0 otherwise.

	The state is a single integer containing information about whether we
	are in a single-quoted state, a double-quoted state, a backslash-escaped
	state, using bitmasks:

	MSH_ESCAPED tells us if we're in a backslash-escaped state
	MSH_SQUOTE tells us if we're in a single-quoted state
	MSH_DQUOTE tells us if we're in a double-quoted state

	& is used to check a bit,
	^= is used to flip a bit,
	|= is used to set a bit,
	&= ~ is used to clear a bit.

	Note: in the case of the backslash, the state is not enough to determine
	whether the character represents itself or not. We also have to look at
	the next character.

	Ex1: "hello\"world". Here, we are in double-quoted state, and the backslash
	escapes the double-quote.
	Ex2: "hello\'world". Here, we are in double-quotes state as well, but the
	backslash doesn't escape the single-quote since the single-quote doesn't
	need to be escaped.
*/
int	update_state(char *c, int *state)
{
	int	ret;

	ret = 1;
	if (*c == '\'' && !(*state & MSH_DQUOTE) && !(*state & MSH_ESCAPED))
	{
		*state ^= MSH_SQUOTE;
	}
	else if (*c == '"' && !(*state & MSH_SQUOTE) && !(*state & MSH_ESCAPED))
	{
		*state ^= MSH_DQUOTE;
	}
	else if (*c == '\\' && !(*state & MSH_SQUOTE) && !(*state & MSH_ESCAPED)
		&& needs_escaping(*(c + 1), *state))
	{
			*state |= MSH_ESCAPED;
	}
	else
	{
		ret = 0;
		*state &= ~MSH_ESCAPED;
	}
	return (ret);
}

/*
	Checks if, in the given state, this character would need to be escaped.

	Ex1: In a normal state, the character `a' doesn't need to be escaped.
	Ex2: In a double-quoted state, the character `$' would need to be escaped.
*/
static int	needs_escaping(char c, int state)
{
	return (c == '\\'
		|| c == '"'
		|| (c == '\'' && !(state & MSH_DQUOTE))
		|| (c == '$')
		|| (c == '*' && !(state & MSH_DQUOTE)));
}

#define ESC_DEFAULT_CHARS	"\"\\$'"
#define ESC_DQUOTED_CHARS	"\"\\$"

/*
	Escape some special characters.
	A backslash is placed before each of these characters.

	Result is x_malloc()-ed.

	If flag is ESC_DEFAULT_CHARS (0), escape all characters that need to be escaped
	during param expansion or filename generation.
	These are: " \ $ '

	Else if flag is set to ESC_DQUOTED_CHARS (1), escape only characters that
	need to be escaped in a double quoted state.
	These are: " \ $
*/
char	*escape_special_chars(char *str, int flag)
{
	int		i;
	char	*res;
	char	*chars;

	if (flag == ESC_TYPE_DQUOTED)
		chars = ESC_DQUOTED_CHARS;
	else
		chars = ESC_DEFAULT_CHARS;
	res = x_malloc(sizeof(char), 2 * ft_strlen(str) + 1);
	i = 0;
	while (*str)
	{
		if (ft_strchr(chars, *str))
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
