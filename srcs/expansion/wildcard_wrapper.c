/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:30:29 by znichola          #+#    #+#             */
/*   Updated: 2023/02/07 17:04:52 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wildcard_wrapper(t_item *item)
{
	char	*tmp;

	if (item == NULL)
		return ;
	tmp = NULL;
	if (find_wildcard_matches(&tmp, item->word) == 1)
	{
		free(item->word);
		item->word = tmp;
	}
	// wildcard_expand(item->next);
	return ;
}
