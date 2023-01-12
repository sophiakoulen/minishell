/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:51:33 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/12 14:58:45 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	do_heredoc(const char *delim, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line()
	}
}

int	count_heredoc(t_pipeline *pipeline)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < pipeline->n_cmds)
	{
		if (pipeline->cmds[i]->in->type == IS_HEREDOC)
		{
			count++;
		}
		i++;
	}
	return (count);
}

