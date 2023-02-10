/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:51:06 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/10 10:24:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_endl(char *line);

char	*get_input_line(char *prompt)
{
	char	*line;

	if (isatty(0) && isatty(2))
	{
		line = readline(prompt);
	}
	else
	{
		line = get_next_line(0);
		remove_endl(line);
	}
	return (line);
}

/*
	Modifies the string!!
	Just removes the first \n if it exists
*/
static void	remove_endl(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}
