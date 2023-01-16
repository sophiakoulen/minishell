/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:23 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 13:40:26 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_fds *fds, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		close(fds->hd_pipes[i][0]);
		close(fds->hd_pipes[i][1]);
		close(fds->infile_fds[i]);
		close(fds->outfile_fds[i]);
		if (i == n - 1)
			break ;
		close(fds->pipes[i][0]);
		close(fds->pipes[i][1]);
		i++;
	}
}
