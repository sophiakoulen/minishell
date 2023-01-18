/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:02:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/18 23:54:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	expand a string, either for redir item or ags list
	well no, maybe use this only for args expansion?
 */
t_list **str_expansion(char *str)
{
	t_list	*words;

	words = ft_lstnew(NULL);
}

		// if ((*str)[i] == 34)
		// 	double_q ^= 1U;
		// if ((*str)[i] == 39)
		// 	single_q ^= 1U;
		// if (!single_q)
		// 	if (!double_q)
//  no split 'this "is small" $VAR quotes'
static void	next_word(t_list *word, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!str)
		return ;

	// found single quote
	// everything needs to be added untill the next one if found
	if (*str == SINGLE_QUOTE)
	{
		tmp = ft_strchr(str, SINGLE_QUOTE);
		if (tmp == NULL)
			perror("not closing ' but should ont be possible");
		word->content = ft_substr(str, 1, tmp - str);
	}
}

void	args_print(t_list *word)
{
	if (word == NULL)
		return ;
	ft_printf("{%s}", (char *)word->content);
	args_print(word->next);
}
