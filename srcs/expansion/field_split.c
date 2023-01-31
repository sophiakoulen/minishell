/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:49:13 by znichola          #+#    #+#             */
/*   Updated: 2023/01/31 10:43:25 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	SO I propose using a new variable to make the connection between parsing and expansion.
	these are my notes to get a handle on the structure used int t_parsed_pipeline
	t_list                *inter_pipe_lst;

	this is an inter_pipe_lst I'm pretty sure

	t_parsed_pipeline    *parsed;
	change to a
	t_list.              *inter_pipe_lst

	t_list inter_pipe_lst
		 -> t_parsed_cmd *cmd
				-> t_list *args
					-> content
						t_item *item
							char    *word;
							int        modifier;
					-> next
				-> t_list *redirs
					-> content
						t_item *item
							char    *word;
							int        modifier;
					-> next
		-> next
*/

/*
	Word expansion order of operations

	1. expand parameter, $VAR, $?
		param_expansion();
	2. field splitting around T_IFS characters
		field_split();
	3. remove quotes
		quote_removal();
 */

static char		*get_word(char **str);
static t_item	*create_chunk(char *str, int modifier);

/*
	Replace the pointed item with multiple items.

	The number of items generated is returned.
	This number can be zero!
*/
int	field_split(t_item **item)
{
	t_item	*chunk;
	t_item	*next;
	int		i;

	chunk = create_chunk((*item)->word, (*item)->modifier);
	if (!chunk)
		return (0);
	next = (*item)->next;
	(*item)->next = NULL;
	free((*item)->word);
	free(*item);
	*item = chunk;
	i = 0;
	while (1)
	{
		i++;
		if (chunk->next)
			chunk = chunk->next;
		else
		{
			chunk->next = next;
			break ;
		}
	}
	return (i);
}

static t_item	*create_chunk(char *str, int modifier)
{
	t_item	*chunk;
	t_item	**current;
	char	*wrd;

	chunk = NULL;
	current = &chunk;
	while (1)
	{
		wrd = get_word(&str);
		if (!*wrd)
		{
			free(wrd);
			break ;
		}
		*current = item_factory(&(t_item){wrd, modifier, NULL});
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
