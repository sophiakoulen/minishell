/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:51:33 by skoulen           #+#    #+#             */
/*   Updated: 2023/02/12 18:10:22 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_line(char **buffer, char *line);

/*
	For each command that has a heredoc, write it's heredoc
	input to the corresponding pipe. Then close the pipe.
*/
void	write_all_heredocs(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n)
	{
		if (exec->cmds[i].hd_buffer)
		{
			write(exec->hd_pipes[i][1],
				exec->cmds[i].hd_buffer,
				ft_strlen(exec->cmds[i].hd_buffer));
			close(exec->hd_pipes[i][1]);
		}
		i++;
	}
}

/*
	Read input from stdin into a buffer, until delim is found.
*/
void	read_single_heredoc(char **buffer, char *delim)
{
	char	*line;

	free(*buffer);
	*buffer = ft_strdup("");
	while (1)
	{
		line = get_input_line("> ");
		if (line == NULL || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		add_line(buffer, line);
	}
}

/*
	Add a line to buffer and a newline.
	line is then freed.
*/
static void	add_line(char **buffer, char *line)
{
	char	*tmp;
	int		size;

	size = ft_strlen(line) + 2;
	if (*buffer)
		size += ft_strlen(*buffer);
	tmp = x_malloc(sizeof(*tmp), size);
	if (*buffer)
	{
		ft_strlcpy(tmp, *buffer, size);
		ft_strlcat(tmp, line, size);
	}
	else
	{
		ft_strlcpy(tmp, line, size);
	}
	tmp[size - 2] = '\n';
	tmp[size - 1] = '\0';
	free(*buffer);
	free(line);
	*buffer = tmp;
}
