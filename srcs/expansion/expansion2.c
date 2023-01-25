/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:19:53 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/25 16:49:19 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Word expansion order of operations

	1. expand parameter, $VAR, $?
		param_expansion();
	2. field splitting around T_IFS characters
		field_split();
	3. remove quotes
		quote_removal();
 */

static t_list	*apply_all(char *str, t_env *env, int retn);
static void		remove_all_quotes(t_list *lst);
static int		expand_redir(char *str, t_env *env, int retn, char **res);

/*
	Generate a new list of expanded words.
	The size of the list may differ.
*/
t_list	*expand_args_list(t_list *lst, t_env *env, int retn)
{
	t_list	*current;
	t_list	*chunk;
	t_list	*start;
	t_list	**ptr;

	current = lst;
	ptr = NULL;
	start = NULL;
	while (current)
	{
		chunk = apply_all(current->content, env, retn);
		if (!start)
			start = chunk;
		if (ptr)
			*ptr = chunk;
		while (chunk)
		{
			ptr = &chunk->next;
			chunk = chunk->next;
		}
		current = current->next;
	}
	return (start);
}

int	expand_redirs(t_list *redirs, t_env *env, int retn)
{
	t_list	*current;
	t_item	*redir;
	char	*tmp;

	current = redirs;
	while (current)
	{
		redir = current->content;
		if (redir->modifier == e_heredoc)
		{
			redir->word = ft_strdup(redir->word);
		}
		else
		{
			if (expand_redir(redir->word, env, retn, &tmp) != 0)
			{
				redir->word = tmp;
				return (-1);
			}
			redir->word = tmp;
		}
		current = current->next;
	}
	return (0);
}

static int	expand_redir(char *str, t_env *env, int retn, char **res)
{
	char	*step1;
	t_list	*step2;

	step1 = param_expansion(str, env, retn);
	step2 = field_split(step1);
	free(step1);
	if (!step2 || step2->next)
	{
		print_error(0, str, "ambiguous redirect");
		ft_lstclear(&step2, free);
		*res = ft_strdup("");
		return (-1);
	}
	remove_all_quotes(step2);
	*res = step2->content;
	ft_lstclear(&step2, do_nothing);
	return (0);
}

/*
	Generate a list of expanded strings from a single string.
*/
static t_list	*apply_all(char *str, t_env *env, int retn)
{
	char	*step1;
	t_list	*step2;

	step1 = param_expansion(str, env, retn);
	step2 = field_split(step1);
	free(step1);
	remove_all_quotes(step2);
	return (step2);
}

static void	remove_all_quotes(t_list *lst)
{
	t_list	*current;
	char	*tmp;

	current = lst;
	while (current)
	{
		tmp = quote_removal(current->content);
		free(current->content);
		current->content = tmp;
		current = current->next;
	}
}
