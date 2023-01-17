/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:51:33 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/17 11:52:58 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delim(char *line, const char *delim);
static void	add_line(char **buffer, char *line);
static void	do_single_heredoc(const char *delim, int fd);

/*
	For each command, write heredoc to corresponding pipe
	if needed.

	Function should be called in the parent process.

	hd_pipes is an array of pipes the parent process
	should write to.
*/
void	do_all_heredocs(t_cmd *cmds, int **hd_pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (cmds[i].in && cmds[i].in->type == e_heredoc)
		{
			do_single_heredoc(cmds[i].in->str, hd_pipes[i][1]);
		}
		i++;
	}
}

/*
	Writes input from stdin to a file descriptor,
	until the delim string, on its own line,
	is reached and closes the file descriptor.

	This function should be called in the parent process,
	to execute here-documents.

	The fd should be the write end of a pipe, and a child
	process should read at the read end of that pipe.
*/
static void	do_single_heredoc(const char *delim, int fd)
{
	char	*buffer;
	char	*line;

	buffer = 0;
	while (1)
	{
		line = readline("> ");
		if (is_delim(line, delim))
		{
			free(line);
			break ;
		}
		add_line(&buffer, line);
	}
	if (buffer)
		ft_putstr_fd(buffer, fd);
	close(fd);
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
	free(*buffer);
	free(line);
	*buffer = tmp;
}
