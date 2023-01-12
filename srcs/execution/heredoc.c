/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:51:33 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/13 18:18:04 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delim(char *line, const char *delim);
static void	add_line(char **buffer, char *line);

/*
	Writes input from stdin to a file descriptor,
	until the delim string, on its own line,
	is reached and closes the file descriptor.

	This function should be called in the parent process,
	to execute here-documents.

	The fd should be the write end of a pipe, and a child
	process should read at the read end of that pipe.
*/
void	do_single_heredoc(const char *delim, int fd)
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

static void	add_line(char **buffer, char *line)
{
	char	*tmp;
	int		size;

	size = ft_strlen(line) + 2;
	if (*buffer)
		size += ft_strlen(*buffer);
	tmp = malloc(size * sizeof(*tmp));
	if (!tmp)
	{
		perror(0);
		exit(2);
	}
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

/*
void	do_all_heredoc(int n, char **delims, int *fds)
{
	int	i;

	i = 0;
	while (i < n)
	{
		do_1heredoc(delims[i], fds[i]);
		i++;
	}
}
*/

/*
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
*/
