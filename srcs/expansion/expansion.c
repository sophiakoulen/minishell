/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 11:05:42 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_cmd(t_item **cmd, t_env *env, int retn);
static int	expand_item(t_item **item, t_env *env, int retn);

/*
	Perform expansion on each command, i.e, each item in
	the pipeline list.
*/
int	expand_pipeline(t_list **pipeline, t_env *env, int retn)
{
	t_list	*current;
	t_item	**cmd;

	current = *pipeline;
	while (current)
	{
		cmd = (t_item **)&current->content;
		if (expand_cmd(cmd, env, retn) != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

/*
	Perform expansion on a command. That means, expansion
	on each item of the command list. The number of items
	in the list might change in this phase.
*/
static int	expand_cmd(t_item **cmd, t_env *env, int retn)
{
	t_item	**current;

	current = cmd;
	while (*current)
	{
		if (expand_item(current, env, retn) != 0)
			return (-1);
		current = &(*current)->next;
	}
	return (0);
}

/*
	Perform parameter expansion, filed-splitting and
	quote-removal.
	If the item is a heredoc redirection, only quote-removal
	is done.
	Return -1 in case of ambiguous redirect.
*/
static int	expand_item(t_item **item, t_env *env, int retn)
{
	char	*tmp;
	char	*word;
	int		n;

	word = ft_strdup((*item)->word);
	if ((*item)->modifier != e_heredoc)
	{
		tmp = param_expansion((*item)->word, env, retn);
		free((*item)->word);
		(*item)->word = tmp;
		n = field_split(item);
		if ((*item)->modifier != NO_MODIFIER && n != 1)
		{
			print_error(0, word, "ambiguous redirect");
			free(word); //ugly
			return (-1);
		}
	}
	tmp = quote_removal((*item)->word);
	free((*item)->word);
	(*item)->word = tmp;
	free(word);
	return (0);
}
