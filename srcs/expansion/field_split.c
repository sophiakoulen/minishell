/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:49:13 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 12:55:11 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_word(char **str);

t_item	*field_split(t_item *item)
{
	t_item	*chunk;
	t_item	**current;
	char	*str;
	char	*wrd;

	chunk = NULL;
	current = &chunk;
	str = item->word;
	while (1)
	{
		wrd = get_word(&str);
		if (!*wrd)
		{
			free(wrd);
			break ;
		}
		*current = item_factory(&(t_item){wrd, item->modifier, NULL});
		current = &(*current)->next;
	}
	return (chunk);
}

static char	*get_word(char **str)
{
	char	*word;
	int		state;
	int		i;

	state = 0;
	while (**str && ft_strchr(T_IFS, **str))
		(*str)++;
	i = 0;
	while ((*str)[i])
	{
		update_state(*str + i, &state);
		if (!(state & MSH_ESCAPED || state & MSH_DQUOTE || state & MSH_SQUOTE)
			&& ft_strchr(T_IFS, (*str)[i]))
			break ;
		i++;
	}
	word = ft_substr((*str), 0, i);
	*str += i;
	return (word);
}
