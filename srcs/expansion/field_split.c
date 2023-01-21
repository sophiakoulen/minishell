/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:49:13 by znichola          #+#    #+#             */
/*   Updated: 2023/01/21 01:13:48 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	t_list				*inter_pipe_lst;

	this is an inter_pipe_lst I'm pretty sure

	t_parsed_pipeline	*parsed;
	change to a t_list

	t_list inter_pipe_lst
		 -> t_parsed_cmd *cmd
				-> t_list *args
					-> content
						t_item *item
							char	*word;
							int		modifier;
					-> next
				-> t_list *redirs
					-> content
						t_item *item
							char	*word;
							int		modifier;
					-> next
		-> next
*/

/*
	The great word expansion order

	1. expand parameter, $VAR, $?
		param_expansion();
	2. field splitting around T_IFS characters
		field_split();
	3. remove quotes
		quote_removal();

 */

t_list	*field_split(char *str)
{
	t_list	*words;


}

static	word_expansion(t_parsed_pipeline *pp, t_env *env, int retn)
{
	t_list				*words;
	t_parsed_cmd		*cmd;
	t_parsed_pipeline	*newpp;
	int					i;
	char				*tmp;

	i = -1;
	while (i++ < pp->n_cmds)
	{
		tmp = param_expansion(pp->cmds[i], env, retn);
	}
}
