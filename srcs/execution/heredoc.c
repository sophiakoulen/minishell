/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:51:33 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/30 14:56:31 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delim(char *line, const char *delim);
static void	add_line(char **buffer, char *line);
static void	read_single_heredoc(t_cmd *cmd);

/*
	For each command that has a heredoc, read the heredoc
	input into a buffer.
	Input is read from stdin until the corresponding delimiter
	is found.
*/

void	read_all_heredocs(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n)
	{
		if (exec->cmds[i].has_heredoc)
		{
			read_single_heredoc(&exec->cmds[i]);
		}
		i++;
	}
}

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
		if (exec->cmds[i].has_heredoc)
		{
			write(exec->hd_pipes[i][1],
				exec->cmds[i].hd_buffer,
				ft_strlen(exec->cmds[i].hd_buffer));
			close(exec->hd_pipes[i][1]);
			free(exec->cmds[i].hd_buffer);
		}
		i++;
	}
}

/*
	Read input from stdin into a buffer, until delim is found.
*/
static void	read_single_heredoc(t_cmd *cmd)
{
	char	*buffer;
	char	*line;

	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (line == NULL || is_delim(line, cmd->hd_delim))
		{
			free(line);
			break ;
		}
		add_line(&buffer, line);
	}
	cmd->hd_buffer = buffer;
}

/*
	check if line is equal to the delimiter
*/
static int	is_delim(char *line, const char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if (ft_strncmp(line, delim, len + 1) == 0)
	{
		return (1);
	}
	else
	{
		return (0);
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
