/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:16:52 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 12:38:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*x_malloc(size_t size, size_t quantity)
{
	void	*ret;

	ret = (void *)malloc(size * quantity);
	if (!ret)
	{
		perror("failed to allocate more memory, quitting.");
		// our clean up function! but maybe we don't need it.
		exit(2);
	}
	return (ret);
}
