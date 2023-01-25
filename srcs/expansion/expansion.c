/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/25 12:46:22 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**list_to_array(t_list *lst);

/*
	Transform the parsed pipeline into a definitive pipeline.
	That means, expansion is performed on all the commands.
*/
int	expand_pipeline(t_pipeline **p, t_parsed_pipeline *intermediate, t_env *env, int retn)
{
	int			i;

	*p = x_malloc(sizeof(**p), 1);
	(*p)->n_cmds = intermediate->n_cmds;
	(*p)->cmds = x_malloc(sizeof(*((*p)->cmds)), (*p)->n_cmds);
	i = 0;
	while (i < (*p)->n_cmds)
	{
		if (expand_cmd(&(*p)->cmds[i], intermediate->cmds[i], env, retn) != 0)
		{
			pipeline_cleanup(*p);
			return (-1);
		}
		i++;
	}
	return (0);
}

/*
	Transform the parsed command into a definitive command.
	That means, string expansion is performed of both the argument list
	and the rediretion list.
*/
int	expand_cmd(t_cmd *definitive, t_parsed_cmd *intermediate, t_env *env, int retn)
{
	t_list	*expanded_args;

	/* expand arguments */
	expanded_args = expand_args_list(intermediate->args, env, retn);
	definitive->args = list_to_array(expanded_args);
	ft_lstclear(&expanded_args, do_nothing);

	/* expand redirections */
	
	if (expand_redirs(intermediate->redirs, env, retn) != 0)
	{
		return (-1);
	}
	definitive->redirs = intermediate->redirs;
	return (0);
}

static char	**list_to_array(t_list *lst)
{
	char			**array;
	int				size;
	int				i;

	size = ft_lstsize(lst);
	array = x_malloc(sizeof(*array), size + 1);
	i = 0;
	while (lst)
	{
		array[i] = lst->content;
		lst = lst->next;
		i++;
	}
	array[i] = 0;
	return (array);
}
