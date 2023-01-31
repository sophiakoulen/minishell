/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 14:52:36 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_cmd(t_item **cmd, t_env *env, int retn);
static int	expand_item(t_item *item, t_item **res, t_env *env, int retn);
static void	lst_quote_removal(t_item *lst);

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
	Perform expansion on a command.

	Generate an expanded list of commands and free the original.
*/
static int	expand_cmd(t_item **cmd, t_env *env, int retn)
{
	t_item	*current;
	t_item	*new_chunk;
	t_item	*res;
	t_item	**ptr;
	int		ret;

	ret = 0;
	res = NULL;
	ptr = &res;
	current = *cmd;
	while (current)
	{
		if (expand_item(current, &new_chunk, env, retn) != 0)
			ret = -1;
		*ptr = new_chunk;
		while (*ptr)
			ptr = &(*ptr)->next;
		current = current->next;
	}
	item_list_cleanup(*cmd);
	*cmd = res;
	return (ret);
}

/*
	Perform expansion on the given item.

	That means:
	1. perform param expansion on the item->word.
	2. Split the item->word: the single list item can know expand
		to zero, one or more items. The field_split function
		modifies the list.
	3. Perform quote removal on the expanded items.

	If the item is a heredoc redirection, only quote-removal
	is done.
	Return -1 in case of ambiguous redirect.
*/
static int	expand_item(t_item *item, t_item **res, t_env *env, int retn)
{
	char	*tmp;
	char	*word;
	int		ret;

	ret = 0;
	word = ft_strdup(item->word);
	if (item->modifier != e_heredoc)
	{
		tmp = param_expansion(item->word, env, retn);
		free(item->word);
		item->word = tmp;
		*res = field_split(item);
		if (item->modifier != NO_MODIFIER && (!*res || (*res)->next))
		{
			print_error(0, word, "ambiguous redirect");
			ret = -1;
		}
	}
	else
		*res = item_factory(&(t_item){ft_strdup(word), e_heredoc, NULL});
	lst_quote_removal(*res);
	free(word);
	return (ret);
}

static void	lst_quote_removal(t_item *lst)
{
	char	*tmp;

	while (lst)
	{
		tmp = quote_removal(lst->word);
		free(lst->word);
		lst->word = tmp;
		lst = lst->next;
	}
}
