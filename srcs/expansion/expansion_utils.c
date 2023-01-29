/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:59:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/29 14:07:46 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MSH_DQUOTE	1U
#define MSH_SQUOTE	2U
#define MSH_ESCAPED	4U

static int	needs_escaping(char c, int state);

/*
	Check if the character has special meaning and update the state
	accordingly.

	Return value:
	1 if character has special meaning, i.e, it doesn't represent itself.
	0 otherwise.

	The state is a single integer containing information about whether we
	are in a single-quoted state, a double-quoted state, a backslash-escaped
	state.
	The operations are done using bitwise operations, since the states can be
	represented using 3 bits.

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
	Checks whether the character would need to be escaped in the
	given state.
*/
static int	needs_escaping(char c, int state)
{
	return (c == '\\'
		|| c == '"'
		|| (c == '\'' && !(state & MSH_DQUOTE)));
}
