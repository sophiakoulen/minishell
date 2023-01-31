/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:49:13 by znichola          #+#    #+#             */
/*   Updated: 2023/01/31 14:32:32 by skoulen          ###   ########.fr       */
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
	int		dquote;
	int		squote;
	int		escaped;
	int		i;

	dquote = 0;
	squote = 0;
	escaped = 0;
	while (ft_isspace(**str))
		(*str)++;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !dquote && !escaped)
		{
			squote = !squote;
		}
		if ((*str)[i] == '"' && !squote && !escaped)
		{
			dquote = !dquote;
		}
		if ((*str)[i] == '\\' && !escaped)
		{
			escaped = 1;
		}
		else
		{
			escaped = 0;
		}
		if (!dquote && !squote && !escaped && ft_isspace((*str)[i]))
				break ;
		i++;
	}
	word = ft_substr((*str), 0, i);
	*str += i;
	return (word);
}
