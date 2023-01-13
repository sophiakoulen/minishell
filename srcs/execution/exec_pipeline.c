/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/12 14:46:00 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef	s_exec
{
	int		*pipes;
	int		*hd_pipes;
}	t_exec;

typedef s_cmd_internal
{
	int		ifd;
	int		ofd;
	char	*full_path;
	int		status;
}	t_cmd_internal;

/*
	Execute pipeline and return exit status of last command.

	Needs the environment to work with and send to child processes.
*/
int	exec_pipeline(t_pipeline *pipeline, t_env environment)
{
	int	exit_status;

	//prepare file descriptors
	
	//launch all children
	
	//do heredoc
	
	//close file descriptors in the parent

	//wait for all children

	//compute return value.
	return (exit_status);
}

int	prepare_file_descriptors(t_pipeline *pipeline)
{
	//open pipes
	//open input and output files
	//open heredoc pipes
	
	int	n_pipes = pipeline->size - 1;
	int	*pipes = open_pipes(n_pipes);

	

	return (0);
}

int prepare_input(t_cmd *cmd)
{
	char	*str;
	int		fd;

	str = cmd->in->str;
	if (cmd->in->type == INFILE)
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
		{
			//error handling here
		}
	}
	else
	{
		int hd[2];
	
		pipe(hd);

	}
}

int	prepare_output(t_cmd *cmd)
{
	char	*filename;
	int		fd;
	int		flags;

	filename = cmd->out->str;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->out->type == IS_APPEND)
	{
		flags |= O_APPEND;
	}
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		//error handling here
	}
	return (fd);
}
