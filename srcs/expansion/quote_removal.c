/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:02:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/29 18:39:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Remove quotes, repecting escaped sequences.

	Iterate through the string, keeping track of and updating the state:
	Single-quoted or double-quoted, and whether we are in a
	backslash-escaped state.

	The update_state() function returns true if the character is not to be
	kept in the string, which can be deduced using the state.

	We use that to decide whether or not to add or not the characters from our
	str argument to the returning string.
*/
char	*quote_removal(char *str)
{
	int		state;
	int		i;
	char	*res;

	res = x_malloc(1, ft_strlen(str) + 1);
	state = 0;
	i = 0;
	while (*str)
	{
		if (!update_state(str, &state))
		{
			res[i] = *str;
			i++;
		}
		str++;
	}
	res[i] = 0;
	return (res);
}
