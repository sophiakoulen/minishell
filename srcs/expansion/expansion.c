/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 16:50:28 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_all_quotes(t_item *lst);
static int	expand_cmd(t_item **cmd, t_env *env, int retn);

/*
	Transform the parsed pipeline into a definitive pipeline.
	That means, expansion is performed on all the commands.
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
	Transform the parsed command into a definitive command.
	That means, string expansion is performed of both the argument list
	and the rediretion list.
*/
static int	expand_cmd(t_item **cmd, t_env *env, int retn)
{
	t_item	**current;
	char	*wrd;
	int		n;
	int		ret;

	ret = 0;
	current = cmd;
	while (*current)
	{
		if ((*current)->modifier != e_heredoc)
		{
			wrd = (*current)->word;
			(*current)->word = param_expansion((*current)->word, env, retn);
			n = field_split(current);
			if ((*current)->modifier != NO_MODIFIER && n != 1)
			{
				print_error(0, wrd, "ambiguous redirect");
				ret = -1;
			}
		}
		else
		{
			(*current)->word = ft_strdup((*current)->word);
		}
		current = &(*current)->next;
	}
	remove_all_quotes(*cmd);
	return (ret);
}

static void	remove_all_quotes(t_item *lst)
{
	t_item	*current;
	char	*tmp;

	current = lst;
	while (current)
	{
		tmp = quote_removal(current->word);
		free(current->word);
		current->word = tmp;
		current = current->next;
	}
}
