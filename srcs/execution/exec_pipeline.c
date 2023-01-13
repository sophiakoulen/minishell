/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/13 17:43:20 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Execute pipeline and return exit status of last command.

	Needs the environment to work with and send to child processes.

	If there is only one command, we don't fork.
*/
int	exec_pipeline(t_pipeline *p, t_env *environment)
{
	t_fds	*fds;
	int		ret;

	fds = prepare_fds(p);
	if (p->n_cmds < 2)
	{
		ret = simple_command(p->cmds[0], environment);
	}
	else
	{
		ret = multiple_commands(p, environment);
	}
	cleanup_fds(fds);
	return (ret);
}

int	simple_command(t_cmd *cmd, t_env *environment)
{
	//redirect input and output
	//is it a builtin? then exec builtin
	//else exec command
	//undo redirect input and output!!
}
